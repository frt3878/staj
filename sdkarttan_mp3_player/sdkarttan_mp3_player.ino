#include "Arduino.h"
#include "Audio.h"
#include "SD.h"
#include "FS.h"
 
// Digital I/O used
#define SD_CS          5   // cihaz slect pin 
#define SPI_MOSI      23    // SD Card
#define SPI_MISO      19
#define SPI_SCK       18
 
#define I2S_DOUT      25
#define I2S_BCLK      27    // I2S
#define I2S_LRC       26
 
Audio audio;
 
void setup() {
    pinMode(SD_CS, OUTPUT);      
    digitalWrite(SD_CS, HIGH);
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    Serial.begin(115200);// serial monitörü 115200 baud ile başlat . 
    if(!SD.begin(SD_CS))//sd kart ile bağlantı yoksa if statemant gir 
    {
      Serial.println("Sd kart ile baglanti kurulamadi");
      while(true);  // Baglanti kurulamazsa bekle 
    }
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);// I2S protokolü başlatma 
 
    audio.connecttoFS(SD,"/test.mp3");// sd kartın içinde bulunan test.mp3 ü çaldırmaya başla . 
}
 
void loop()
{
    audio.loop();    
}
 
