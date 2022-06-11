# Application-side  

## Complete_pro  
->学内の産学連携プロジェクトで使用したコードです。  
・M5Stack+Blynk+Google Apps Script  
・開発環境 vsCode (PlatformIO)  
Complete_pro/  
    　├ src/main.cpp メインソースファイル  
    　├ src/GasCommand.cpp Google Apps Script操作用ソースファイル  
    　├ src/SensorControl.cpp センサ値操作用ソースファイル  
    　├ include/GasCommand.h センサ値操作用ヘッダファイル  
    　├ include/SensorControl.h センサ値操作用ヘッダファイル  

・システムの概要図  
　握力補助デバイス開発のアプリケーションサイドを担当しました  

・機能  
　＞センサ感度調整機能  
　＞緊急停止機能（SOS）  
　＞動作履歴閲覧機能  
![system2](https://user-images.githubusercontent.com/74394877/173171733-a0f84bf0-f38b-41dc-9231-88cc6c2712d3.png)

スマートフォン上のBlynkアプリケーション画面  
左から、緊急停止ボタン、履歴閲覧ボタン、センサー感度調整ボタン、動作記録用スプレッドシート  

![monoスクリーン](https://user-images.githubusercontent.com/74394877/173171736-d436d7f0-d02f-458e-88ad-019c837caaa6.png)
