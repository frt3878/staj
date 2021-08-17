#include <WiFi.h>
#include <Wire.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "index.h"

const char* ssid = "Yesil";
const char* password = "sste0102";

String veri = "1";
int16_t data[6];// okunacak veriler


WebServer server(80);

void handleRoot() 
{
 String s = webpage;
 server.send(200, "text/html", s);
}

void sensor_data() 
{
  Wire.beginTransmission(0x68);
  /* I2C haberleşmesi yapılacak kart seçildi */
  Wire.write(0x3B); 
  /* 0x3B adresindeki register'a ulaşıldı */
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,14,true);
  /* 14 BYTE'lık veri istendi */
  
  data[0]=Wire.read()<<8|Wire.read();   
  data[1]=Wire.read()<<8|Wire.read(); 
  data[2] =Wire.read()<<8|Wire.read(); 
  data[3]=Wire.read()<<8|Wire.read(); // sıcaklık verisi 
  data[4]=Wire.read()<<8|Wire.read(); 
  data[5]=Wire.read()<<8|Wire.read();  
  data[6]=Wire.read()<<8|Wire.read();
  veri = String(data[3]/340.00+36.53);
 
 server.send(200, "text/plane", veri);
}

void led_control() 
{
 String state = "OFF";
 String act_state = server.arg("state");
 if(act_state == "1")
 {
  digitalWrite(4,HIGH); //LED ON
  state = "ON";
 }
 else
 {
  digitalWrite(4,LOW); //LED OFF
  state = "OFF";
 }
 server.send(200, "text/plane", state);
}
void setup(void)
{
  pinMode(4,OUTPUT);
  Serial.begin(115200);
  Wire.begin();// sensor haberleşme baslatma 
  Wire.beginTransmission(0x68);// cihaz adresi 0x68 
  Wire.write(0x6B);
  Wire.write(0); /* MPU-6050 çalıştırıldı */
  Wire.endTransmission(true);
  delay(800);
  /*--------------------------------------------------*/
  WiFi.begin(ssid, password);
  Serial.println("");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Connecting...");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.on("/", handleRoot);// web ana ekran
  server.on("/led_set", led_control);// led kontrolü
  server.on("/adcread", sensor_data);// sensor data update 
  server.begin();
}

void loop(void)
{
  server.handleClient();
}
