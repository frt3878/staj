
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
void kurulum();
void setup() {
  Serial.begin(115200);
  pinMode(4,OUTPUT);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  ledcSetup(0, 5000, 8);// frekans 5k resolution 8 chanel 0 
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(4, 0); // pin 4 ch 0

}

    char gelen_data;
    String mesaj;
    char giden_data;
    void loop() {

  
   kurulum();
  }
  void kurulum(){
    
      if (SerialBT.available()) { // eğer data gelmiş ise aşşağıdaki işlemleri yap 
    gelen_data=SerialBT.read();// datayı oku 
    Serial.write(gelen_data);// datayı encode edip bastır 
    
    if(gelen_data != '\n'){ mesaj+=gelen_data; // el ile gelen datayı encode yapma işlemi  
    }
    else{
      int x = mesaj.toInt();// string metnini integera dönüştürme
      ledcWrite(0, x);// pwm duty cycle ayarlama 
      Serial.println(x);// konsola bastırma 
      mesaj = "";// enter karakteri geldiğinde mesajı sıfırlama 
    Serial.println("...");// mesaj sıfırlanınca konsola sinyal bastırma
    }
    
  }
  if (Serial.available()) {// kosolda yazı yollandığını kontrol etme 
    giden_data=Serial.read(); // yazılan yazıyı değişkene atama
    SerialBT.write(giden_data);// bt ile data yollama 
  }
    }
