#include <Arduino.h>
#include <Wire.h>
#include <WireSlave.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#define SDA_PIN 21
#define SCL_PIN 22
#define I2C_SLAVE_ADDR 0x04

int saat;
int dakika;
int saniye;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"pool.ntp.org");
void requestEvent();
const char* ssid = "Yesil";  // wifi adi
const char* password = "******";  //wifi şifresi 

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
  // wifi baglanti kontrol 
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  
  }
 
  Serial.println("WiFi baglanti kuruldu ");
  Serial.print(" IP: ");
  Serial.println(WiFi.localIP());  
    bool res = WireSlave.begin(SDA_PIN, SCL_PIN, 4);
    if (!res) {
        Serial.println("I2C slave init failed");
        while(1) delay(100);
    }

    WireSlave.onRequest(requestEvent);
    Serial.printf("Slave joined I2C bus with addr #%d\n", I2C_SLAVE_ADDR);
 timeClient.begin();
 timeClient.setTimeOffset(10800);
 timeClient.update();
 saat = timeClient.getHours();
 dakika = timeClient.getMinutes();   
 saniye = timeClient.getSeconds();
 Serial.println("saat");
 Serial.println(saat);
}

void loop()
{
   
Serial.println(".");

    delay(100);
}

void requestEvent()
{
    
    WireSlave.write(saat);
}
