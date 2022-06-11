#include <Arduino.h>  //PIOでArduino系統を使用する際必要
#include <M5Stack.h>  //M5Stack用ライブラリ
#include <BlynkSimpleEsp32.h> //Blynk＋ESP32通信ライブラリ
#include <WidgetRTC.h> //BlynkのRTCウィジェット用ライブラリ
#include "SensorControl.h" //センサの値を管理するクラス
#include "GasCommand.h" //gas操作用のクラス

const char* auth = "XXXXXXXXXXXXXX";  //Blynkと連携するためのトークン宣言
const char* ssid = "XXXXXXXXXXXXXX";  //wifiネットワークのSSID宣言
const char* password = "XXXXXXXXXXXXX";  //wifiネットワークのパスワード宣言
const char* address = "XXXXXXXXXXXXXXXX"; //メールアドレス宣言
const String exec_url = "XXXXXXXXXXXXXXXXXXXX";  //GASのウェブアプリケーション識別用URL


bool isSos = false;      //SOS状態であるかどうか判別する変数
float activeTime;    //グローブの動作時間を格納する変数
int saveValue = 1;       //センサ感度を一時的に保存しておく変数
bool isPamActive; //グローブが動作中かを判別する変数

WidgetRTC rtc;    //RTCWidget用のインスタンス
SensorControl sensCtrl = SensorControl(saveValue); //センサ値管理用のインスタンス　引数：初期感度
GasCommand gas; //Gas操作用のインスタンス

//現在の日付を戻り値として返す関数
String CurrentDate()
{
  String date = String(year()) + "/" + month() + "/" + day(); //RTCウィジェットから現在日付を取得
  return date;
}

//現在の時刻を戻り値として返す関数
String CurrentTime()
{
  String time = String(hour()) + ":" + minute() + ":" + second(); //RTCウィジェットから現在時刻を取得
  return time;
}

//LCDを一旦すべてクリアして初期化する関数
void LcdInit()
{
  M5.Lcd.clear(BLACK);               //LCDの画面初期化
  M5.Lcd.setTextSize(2);             //テキストサイズ２
  M5.Lcd.setTextColor(WHITE, BLACK); //黒背景白文字
  M5.Lcd.setCursor(0, 0);            //(0,0)にカーソルを合わせる
}

//SOS状態になっているか常に監視する関数
void SosCheck()
{
  if (!Blynk.connected()) //Blynkサーバーとの接続が切れた場合
  {
    isSos = true; //SOS状態true
    M5.Lcd.print("Blynkdisconnected");
  }

  if(isSos)
  {
    M5.Lcd.println("Emergency"); 
    isSos = false; 
  }
}

//M5の物理ボタンに対応させて実行する関数。
void buttonCheck()
{
  if (M5.BtnA.wasReleased())
  {
    M5.Lcd.println("A : pamActive"); //LCDにAを出力　疑似的なPAM動作状態をつくる
    isPamActive = true;  //PAMが動作中
  }
  if (M5.BtnB.wasReleased())
  {
    M5.Lcd.println("B : pamStop"); //LCDにBを出力　疑似的なPAM停止状態をつくる
    isPamActive = false; //PAMの動作停止
  }
}



//setup用関数。一度だけ実行される
void setup()
{
  M5.begin();           //M5Stack起動させる
  Serial.begin(115200); //シリアル通信レート115200bps
  delay(200); //0.2秒待機
  LcdInit();                     //LCDの初期化関数
  gas.connectingWIFI(ssid,password); //wifiに接続し、結果をresponseに入れる
  Blynk.begin(auth, ssid, password); //wifiに接続し、Blynkサーバとの接続を初期化する
  setSyncInterval(10 * 60);      //サーバ時刻との同期間隔を設定。10[min]ごとに時刻補正
  M5.Lcd.println("Start"); //LCD: "Start"出力


}

//毎フレーム実行される関数
void loop()
{
  Blynk.run(); //Blynkの起動
  M5.update(); //M5Stack内のフレーム更新　物理ボタンを使用する場合に必要
  delay(500); //0.5秒待機
  buttonCheck();  //物理ボタンが押された際実行する関数
  SosCheck(); //SOS状態を監視する関数
}

//Blynkのサーバに接続された時に呼び出される関数
BLYNK_CONNECTED()
{
  Blynk.syncAll(); //オフライン時に行われた値の更新を、Blynk接続時にすべて受け取る
  rtc.begin();     //RTCwidgetを起動用。時刻取得可能
}

//SOSボタンが押された時に呼ばれる////////////////////////
BLYNK_WRITE(V0) //アプリ側からの値の更新があった場合に毎回呼び出される関数
{
  int v0Param = param[0].asInt(); //V0ピンの値をv0Paramに格納
  if (v0Param == HIGH)            //ボタンが押された時実行
  {
    isSos = true;                                                 //グローブサイドの停止コマンド実行
    M5.Lcd.println("sosButton is Pressed");                       //LCDに出力する
    Blynk.email(address, "Blynk", "今、SOSボタンが押されました"); //メールでSOS通知
    gas.writess(exec_url,CurrentDate(),CurrentTime(),"SOSボタン"); //SheetにSOSボタンが押されたことを書き込む
  }
}

//センサ感度の値を一時的に保存する関数/////////////////////////
BLYNK_WRITE(V1)
{
  saveValue = param[0].asInt(); //V1ピンの値をsaveValueに格納
}

//センサ感度の値を確定する関数//////////////////////////
BLYNK_WRITE(V2)
{
  int setButtonValue = param[0].asInt(); //V2ピンの値をsetButtonValueに格納
  if (setButtonValue == HIGH && !isPamActive) //ボタンが押されてかつ、PAMが停止している時に感度確定できる
  {
    sensCtrl.setSensorLevel(saveValue); //センサ感度を上書き
    M5.Lcd.print(sensCtrl.getSensorLevel()); //センサ感度を取得し、LCDに出力    
    gas.writess(exec_url,CurrentDate(),CurrentTime(),"センサ感度：" + String(sensCtrl.getSensorLevel())); //Sheetに感度の更新を書き込む
  }
}
