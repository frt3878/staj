#include <WiFi.h>

const char * ssid = "Yesil";
const char * password = "sifre0102";

void initWiFi() {
  WiFi.mode(WIFI_STA);// wifi modu 
  WiFi.begin(ssid, password);// ag adi ve sifre girilmesi 
  Serial.print("Baglaniyor ");
  while (WiFi.status() != WL_CONNECTED) { // bağlanana kadar bekleme 
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());// ıp adresini bastırma 
}

void setup() {
  Serial.begin(115200); // boudrate ayarlama 
  initWiFi();
  Serial.println(WiFi.RSSI());
}

void loop() {
Serial.println(WiFi.localIP());
delay(4000);
  // put your main code here, to run repeatedly:
}
