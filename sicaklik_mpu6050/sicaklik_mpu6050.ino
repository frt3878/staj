
#include<Wire.h>

const int device=0x68;
// device adress 
int16_t data[6];

void setup(){
  Wire.begin();
  Wire.beginTransmission(device);
  Wire.write(0x6B);
  Wire.write(0); /* device  çalıştırıldı */
  Wire.endTransmission(true);
  /* I2C haberleşmesi başlatıldı  */
  Serial.begin(9600);
}
String veri ="1";
void loop(){
  Wire.beginTransmission(device);
  /* I2C haberleşmesi yapılacak kart seçildi */
  Wire.write(0x3B); 
  /* 0x3B adresindeki register'a ulaşıldı */
  Wire.endTransmission(false);
  Wire.requestFrom(device,14,true);
  /* 14 bytelık veri istendi */
  
  data[0]=Wire.read()<<8|Wire.read();   
  data[1]=Wire.read()<<8|Wire.read(); 
  data[2] =Wire.read()<<8|Wire.read(); 
  data[3]=Wire.read()<<8|Wire.read(); 
  data[4]=Wire.read()<<8|Wire.read(); 
  data[5]=Wire.read()<<8|Wire.read();  
  data[6]=Wire.read()<<8|Wire.read();
  /* Okunan değerler serial monitör'e yazdırılıyor */
  Serial.print("ivmeX = "); Serial.print(data[0]);
  Serial.print(" | ivmeY = "); Serial.print(data[1]);
  Serial.print(" | ivmeZ = "); Serial.print(data[2]);
  veri = String (data[3]/340.00+36.53) ; 
  Serial.print(" | Sicaklik = "); Serial.print(veri );  
  /* Datasheetten alınan sıcaklık hesaplama formülü kullanıldı */
  delay(500);
}
