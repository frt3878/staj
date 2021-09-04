#include "BluetoothA2DPSource.h" // bluetooth ile audio veri yollamak için gerekli kütüphane 
#include <SPI.h>// sd kart ile haberleşmek için spı kütüphanesi 
#include <SD.h>// sd karttan kolay veri almak için kütüphane 
BluetoothA2DPSource a2dp_source;//  BluetoothA2DPSource için obje oluşturma.

File sound_file; 
const char* file_name = "/karayip.raw"; // seçilen ses dosyası karayip korsanları soundtrack
const int frame_size_bytes = sizeof(int16_t) * 2;
int32_t music_data(Channels* data, int32_t len) {// seçilen muzik dosyasının okunabilmesi için . raw veya .wav uzantılı olmalıdır 
  size_t result_len_bytes = sound_file.read((uint8_t*)data, len * frame_size_bytes );
  int32_t result_len = result_len_bytes / frame_size_bytes;
  ESP_LOGD("music_data", "%d -> %d",len );
  Serial.println(result_len);
  return result_len;
}


// Arduino Setup
void setup(void) {
  Serial.begin(115200);

  // Cs pini 5 e bağlı olan sd kartın spı kurulumunu  başlat. 
  SD.begin(5);
  sound_file = SD.open(file_name, FILE_READ);
  // A2dp Baglantı türünü başlat 
  Serial.println(" A2DP Başlatılıyor ...");
  a2dp_source.start("SYX-S16", music_data);  // Syx-S16 bluetooth speakera bağlan ve sd karttan muziği çaldır 
}


void loop() {
}
