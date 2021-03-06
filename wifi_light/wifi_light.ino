#define BLYNK_PRINT Serial
#include <ESP8266WebServer.h>   //AP模式連線
#include <AutoConnect.h>        //AP模式連線
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


const char* ssid = "Redmi";
const char* password = "12345678";
char auth_light[] = "crbCbgnyxVAR9QX4pcOFNWnVEwq3rmDJ";
//---- AP模式連線 -----
ESP8266WebServer Server;
AutoConnect Auto_Connect(Server);
AutoConnectConfig Auto_Connect_config;
//--------------------
void rootPage() { //AP模式連線
  char content[] = "System Starting...";  //顯示系統訊息
  Server.send(200, "text/plain", content);
}
void setup()
{
  // Debug console
  Serial.begin(115200);

  //----- AP模連線設定參數 ------
  Auto_Connect_config.apid = String("智慧插頭");  //AP模WIFI連線帳號
  Auto_Connect_config.psk = String("12345678"); //AP模WIFI連線密碼
  Auto_Connect.config(Auto_Connect_config);
  
  Server.on("/", rootPage);
  if (Auto_Connect.begin()) {  //30秒無法上網，自動啟動AP模式
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
  }
//-------------------------

  Blynk.begin(auth_light, ssid, password,"128.199.173.118",8080);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting...");
  }
}

void loop()
{
  Blynk.run();
  Auto_Connect.handleClient(); //AP模式連線
}
