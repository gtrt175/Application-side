#include "GasCommand.h"



GasCommand::GasCommand()
{
}

GasCommand::~GasCommand()
{
}

//GASにリクエストした値を送信する関数
void GasCommand::postValues(String exec_url , String values){
   WiFiClientSecure client;
   if(client.connect("script.google.com",443)){
      client.println("POST " + exec_url + " HTTP/1.1");
      client.println("HOST: script.google.com");
      client.println("Connection: close");
      client.println("Content-Type: application/json");
      client.print("Content-Length: ");
      client.println(values.length());
      client.println();
      client.println(values);
      while(client.available()){
         client.read();
      }
      client.stop();

   }
}

//設定したアドレスにメール送信をリクエストする関数
void GasCommand::sendMail(String exec_url,String cDate,String cTime,String sensVal){
   String json = String("{\"key1\":\"" + cDate +"\",\"key2\":\"" + cTime + "\",\"key3\":\"" + sensVal + "\",\"mail\":1}");
   postValues(exec_url,json);
}

//設定したgoogleシートに書き込みをリクエストする関数
void GasCommand::writess(String exec_url,String cDate,String cTime,String sensVal){
   String json = String("{\"key1\":\"" + cDate +"\",\"key2\":\"" + cTime + "\",\"key3\":\"" + sensVal + "\",\"ss\":1}");
   postValues(exec_url,json);
}

//Wifiに接続するための関数　10回施行する
String GasCommand::connectingWIFI(const char* ssid ,const char* password){
   WiFi.mode(WIFI_STA);
   WiFi.disconnect();
   WiFi.begin(ssid, password);
   int n_trial=0,max_trial=10;
   while((WiFi.status() != WL_CONNECTED) && (n_trial < max_trial)){
      n_trial++;
      delay(1000);
   }
   if(WiFi.status() == WL_CONNECTED){
      return "connected";
   }else{
      return "connect failed";
   }
}
