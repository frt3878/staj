#include <WiFi.h>

const char * ssid = "Yesil";
const char * password = "sste0102";

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting ");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  initWiFi();
  Serial.println(WiFi.RSSI());
}

void loop() {
Serial.println(WiFi.localIP());
delay(4000);
  // put your main code here, to run repeatedly:
}
