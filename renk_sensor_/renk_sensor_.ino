// TCS34725 0x29
#define device 0x29
#include <Wire.h>

void setup()
{
  Wire.begin(); 
  Serial.begin(9600);
  Wire.beginTransmission(device);
  Wire.write(0x80);
  // Power ON
  Wire.write(0x03);
  Wire.endTransmission();
  delay(800);
}

void loop()
{
  unsigned int data[8];

  // Start I2C Transmission on the device
  Wire.beginTransmission(device);
  Wire.write(0x94);
  Wire.endTransmission();
  Wire.requestFrom(device, 8);
  if (Wire.available() == 8)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
    data[6] = Wire.read();
    data[7] = Wire.read();
  }
  

  // matematiksel hesaplamalar datasheeten alınmıştır 
  float cData = (data[1] * 256.0) + data[0];
  float red = (data[3] * 256.0) + data[2];
  float green = (data[5] * 256.0) + data[4];
  float blue = (data[7] * 256.0) + data[6];
  float luminance = (-0.32466 * red) + (1.57837 * green) + (-0.73191 * blue);

  // Output data to serial monitor
  
  Serial.print("Kirmizi renk yogunlugu   : ");
  Serial.print(red);
  Serial.println(" lux");
  Serial.print("Yesil renk yogunlugu  : ");
  Serial.print(green);
  Serial.println(" lux");
  Serial.print("Mavi renk yogunlugu : ");
  Serial.print(blue);
  Serial.println(" lux");
  Serial.print("Aydinlik : ");
  Serial.print(luminance );
  if((luminance<250)&&(red>green)&&(red>blue))Serial.println("Renk kirmizi");
  if((luminance<250)&&(blue>green)&&(blue>red))Serial.println("Renk mavi");
  if((luminance<250)&&(green>blue)&&(green>red))Serial.println("Renk yesil");
  if(((red-blue)>150) && ((red-green)>150)) Serial.println("Renk kirmizi");
  if(((blue-green)>150) && ((blue-red)>150)) Serial.println("Renk mavi");
  if(((green-blue)>150) && ((green-red)>150)) Serial.println("Renk Yesil ");
  if(((red - green)<100 )&& ((red-blue)>150)&& (( green-blue)>150)) Serial.println("Renk sari ");
  if(((green-red)<100)&&((red-blue)<100)&&((blue-green)<100)&& (luminance>250)) Serial.println("Renk beyaz ");
  if(((green-red)<10)&&((red-blue)<10)&&((blue-green)<10)&& (luminance<100)) Serial.println("Renk siyah ");
  delay(1000);
}
