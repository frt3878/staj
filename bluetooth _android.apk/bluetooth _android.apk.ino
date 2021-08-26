
#include "BluetoothSerial.h"// bluetooth kütüphanesi 
BluetoothSerial SerialBT;// obje oluşturma 
void kurulum();
void setup() {
  Serial.begin(115200);
  pinMode(4,OUTPUT); 
  SerialBT.begin("ESP32test"); //Esp 32 Bluetooth device name
  Serial.println("Bluetooth başlatıldı ");
  // pwm kurulumu pin 4 ch 0 
  ledcSetup(0, 5000, 8);// frekans 5k resolution 8 chanel 0 
  ledcAttachPin(4, 0); // pin 4 ch 0

}
    
    char gelen_data; // bluetooth ile gelen data 
    String mesaj;  // gelen datayı encode edip içine aktardığımız mesaj . 
    char giden_data;// bluetooth ile giden  data 
    int x=0; // pwm duty cycle 
    int temp=0; // sesli komut ile arttırmak ve azaltmak  için değişken 
    void loop() {

  
   kurulum(); // bluetooth data kontrol 
// Sesli komuttan gelen veriler ile kontrol 
   if(mesaj=="aç"){
    ledcWrite(0, 255);
    
    }
    if(mesaj=="kapat"){
    ledcWrite(0, 0);
    
    }
    if(mesaj=="arttır"){
     
    temp=temp+50;
    ledcWrite(0, temp );
    
    }
    if(mesaj=="azalt"){
     
    temp=temp-50;
    ledcWrite(0, temp );
    }
  }
  void kurulum(){
   
    
      if (SerialBT.available()) { // eğer data gelmiş ise aşşağıdaki işlemleri yap 
    gelen_data=SerialBT.read();// datayı oku 
    Serial.write(gelen_data);// datayı encode edip bastır 
    
    if(gelen_data != '\n'){ mesaj+=gelen_data; // el ile gelen datayı encode yapma işlemi  
    }
    else{
       x = mesaj.toInt();// string metnini integera dönüştürme
      if(x==0){}
      else{
      ledcWrite(0, x);// pwm duty cycle ayarlama 
      Serial.println(x);// konsola bastırma 
      }
    mesaj = "";// enter karakteri geldiğinde mesajı sıfırlama 
    Serial.println("...");// mesaj sıfırlanınca konsola sinyal bastırma
    }
    
  }
  if (Serial.available()) {// kosolda yazı yollandığını kontrol etme 
    giden_data=Serial.read(); // yazılan yazıyı değişkene atama
    SerialBT.write(giden_data);// bt ile data yollama 
  }
    }
