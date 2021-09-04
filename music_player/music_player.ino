/*
 * 
pwm ile hoparlörden müzük çaldırmak için 1 tane 250 khz lik pwm kurulmuştur. Sonrasından 8 kHz lik timer kuruulmuştur 
bu timerın görevi 32kHz hız ile alınan duty cycle değerini pwm e sürmektir. Böylelikle örnekleme frekansı 32 kHz olmuş olur .
Resolution ile pwm frekansı ters orantılı olduğundan sesin kalitesini fazla düşürmemek için 8 seçilmiştir. daha yüksek değerlerde
pwm frekansı azalacaktır .

*/

#include <SPI.h>
#include <SD.h>

void okuma();
hw_timer_t * timer = NULL;
File myfile;
int i = 0 ;
 char duty;
void IRAM_ATTR onTimer(){
  
  ledcWrite(0, a[i]);
  i=i+1; 
  if(i==530428) {i=0;}
}


void setup(){
  Serial.begin(115200);

  ledcSetup(0, 250000, 8);// frekans 250k resolution 8 chanel 0 
  ledcAttachPin(4, 0); // pin 4 ch 0
  Serial.println("timer başlat  ");
  timer = timerBegin(0, 80, true);  
  timerAttachInterrupt(timer, &onTimer, true); // edge  triggered 
  timerAlarmWrite(timer, 1000000/32000, true); // 32kHz lik timer.
  timerAlarmEnable(timer); // timer başlat 

  if(!SD.begin(5)){
    Serial.println("Kart bulunamadı");
    return;
  }
  else if (SD.begin(5)){
    Serial.println("Kart bulundu ");
  }
}

void loop() {
}