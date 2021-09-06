#include "mbed.h"

#include "stm32f413h_discovery.h"

#include "stm32f413h_discovery_ts.h"

#include "stm32f413h_discovery_lcd.h"

#include "stm32f413h_discovery_audio.h"

TS_StateTypeDef TS_State = {
  0
};
I2C i2c(PB_11, PB_10);
const int addr = 0x04;
Timer timer1;// saat için timer 
InterruptIn button(USER_BUTTON);// lcd ekran açıp kapamak için onboard üzerindeki buton interrupt 
int saniye = 55;// saniye
int renk = 0;// arka plan rengi
int saat_config = 1;// saat ayarlamak için değişken 
void saniye_timer(void) {// 1 sanielik timer 
  saniye = saniye + 1;

}
void clear(int renk1) {// ekranı temizle ve renk değiştirme
  saat_config = 0;
  if (renk1 == 0) {
    BSP_LCD_Clear(LCD_COLOR_ORANGE);
    BSP_LCD_SetBackColor(LCD_COLOR_ORANGE);
    renk = 1;
  } else if (renk1 == 1) {
    BSP_LCD_Clear(LCD_COLOR_RED);
    BSP_LCD_SetBackColor(LCD_COLOR_RED);
    renk = 2;
  } else if (renk1 == 2) {
    BSP_LCD_Clear(LCD_COLOR_CYAN);
    BSP_LCD_SetBackColor(LCD_COLOR_CYAN);
    renk = 3;
  } else if (renk1 == 3) {
    BSP_LCD_Clear(LCD_COLOR_DARKBLUE);
    BSP_LCD_SetBackColor(LCD_COLOR_DARKBLUE);
    renk = 4;
  } else if (renk1 == 4) {
    BSP_LCD_Clear(LCD_COLOR_DARKCYAN);
    BSP_LCD_SetBackColor(LCD_COLOR_DARKCYAN);
    renk = 5;
  } else if (renk1 == 5) {
    BSP_LCD_Clear(LCD_COLOR_DARKMAGENTA);
    BSP_LCD_SetBackColor(LCD_COLOR_DARKMAGENTA);
    renk = 6;
  } else if (renk1 == 6) {
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    renk = 7;
  } else if (renk1 == 7) {
    BSP_LCD_Clear(LCD_COLOR_DARKRED);
    BSP_LCD_SetBackColor(LCD_COLOR_DARKRED);
    renk = 1;
  }

}
int select = 0;
void on_off(void) {
  if (select == 0) {// buton ile ekran kapayıp açma 
    BSP_LCD_DisplayOff();// ekran kapatma fonksiyonu 
    select = 1;
  } else {
    BSP_LCD_DisplayOn();// lcd ekran açma fonksiyonu 
    select = 0;
  }
  BSP_LCD_Clear(LCD_COLOR_WHITE);// ekran temizlenir ve beyaz renk olur 
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  clear(renk - 1);
  wait_ms(300);
}
 void     AUDIO_DFSDM_DMAx_MIC1_IRQHandler()
{
  printf("ses var 1");
} 
 void     AUDIO_DFSDM_DMAx_MIC2_IRQHandler()
{
  printf("ses var 2");
} 


int main() {
  DigitalIn mic1 (PD_6);
  DigitalIn mic2 (PA_7);
  DigitalIn mic3 (PB_7);
  button.rise( & on_off);// button basıldığında on_off fonksiyonuna git 
  uint16_t x1, y1;// touch screen için değişken 
  timer1.start();// saat için timer başlatma 
  BSP_LCD_Init();

  // Touchscreen initialization */
  if (BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize()) == TS_ERROR) {
    printf("BSP_TS_Init error\n");
  }

  // Clear the LCD */
  BSP_LCD_Clear(LCD_COLOR_WHITE);

  /* Set Touchscreen Demo1 description */

  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

  char * ptr_saniye ;// ekrana basılan saniye bilgisi için char pointer 
  char * ptr_dakika;// ekrana basılan dakika bilgisi için char pointer 
  char * ptr_saat;// ekrana basılan saat bilgisi için char pointer 

  int dakika = 39;
  int saat = 11;
  char c[2];// integer değişkeni char değişkenine dönüştürmek için değişken 
  char d[2];//integer değişkeni char değişkenine dönüştürmek için değişken 
  char e[2];//integer değişkeni char değişkenine dönüştürmek için değişken 
  sprintf(c, "%d", saniye);// integer saniyeyi char değişkenine dönüştürm 
  ptr_saniye = c;
  sprintf(e, "%d", saat);// integer saati char değişkenine dönüştürm 
  ptr_saat = e;

  sprintf(d, "%d", dakika);// integer dakikayı char değişkenine dönüştürm 
  ptr_dakika = d;
  BSP_LCD_Clear(LCD_COLOR_WHITE);
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  while (1) {
    
    sprintf(e, "%d", saat);
    ptr_saat = e;
    if (timer1.read_ms() >= 1000) // timer 1000ms = 1 saniye olduğunda fonksiyona git ve timerı sıfırla 
    {
      saniye_timer(); // timer fonksiyonu 
      timer1.reset(); // reset timer
    }// 

    BSP_LCD_SetFont( & Font12); // font büyüklüğü ayarlama 
    BSP_LCD_DisplayStringAt(160, 20, (uint8_t * )
      "<SetClock>", LEFT_MODE);// x ve y pozisyonları belirlenip ekrana yazı bastırma 
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);// yazılan yazının rengini ayarlama 
    BSP_LCD_DrawCircle(112, 110, 85);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DrawCircle(205, 183, 30);
    BSP_LCD_SetFont( & Font8);
    BSP_LCD_DisplayStringAt(180, 177, (uint8_t * )
      "Background", LEFT_MODE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    if (dakika < 10) {
      BSP_LCD_SetFont( & Font20);
      BSP_LCD_DisplayStringAt(LINE(8), LINE(5), (uint8_t * ) ptr_saniye, LEFT_MODE);
      BSP_LCD_DisplayStringAt(LINE(5), LINE(5), (uint8_t * )
        "0", LEFT_MODE);
      BSP_LCD_DisplayStringAt(LINE(6), LINE(5), (uint8_t * ) ptr_dakika, LEFT_MODE);
      BSP_LCD_DisplayStringAt(LINE(7), LINE(5), (uint8_t * )
        ":", LEFT_MODE);
      BSP_LCD_DisplayStringAt(LINE(2), LINE(5), (uint8_t * ) ptr_saat, LEFT_MODE);
      BSP_LCD_DisplayStringAt(LINE(4), LINE(5), (uint8_t * )
        ":", LEFT_MODE);

    } else {
      BSP_LCD_SetFont( & Font20);
      BSP_LCD_DisplayStringAt(LINE(8), LINE(5), (uint8_t * ) ptr_saniye, LEFT_MODE);
      BSP_LCD_DisplayStringAt(102, LINE(5), (uint8_t * ) ptr_dakika, LEFT_MODE);
      BSP_LCD_DisplayStringAt(LINE(7), LINE(5), (uint8_t * )":", LEFT_MODE);
      BSP_LCD_DisplayStringAt(LINE(2), LINE(5), (uint8_t * ) ptr_saat, LEFT_MODE);
      BSP_LCD_DisplayStringAt(LINE(4), LINE(5), (uint8_t * )":", LEFT_MODE);
    }
    if (saat == 24) {
      clear(renk - 1);
      saat = 0;
      sprintf(e, "%d", saat);
      ptr_saat = e;
    }
    if (saat == -1) {
      clear(renk - 1);
      saat = 24;
      sprintf(e, "%d", saat);
      ptr_saat = e;
    }
    if (saniye == 60) {
      if (renk == 0) clear(6);
      clear(renk - 1);
      dakika = dakika + 1;
      sprintf(d, "%d", dakika);
      ptr_dakika = d;

      saniye = 1;
    }
    if (dakika == 60) {
      dakika = 0;
      clear(renk - 1);
      saat = saat + 1;

    }
    if (dakika == -1) {
      dakika = 60;
      clear(renk - 1);

    }
    sprintf(c, "%d", saniye);
    ptr_saniye = c;
    sprintf(d, "%d", dakika);
    ptr_dakika = d;
    BSP_LCD_SetFont( & Font12);

    BSP_TS_GetState( & TS_State);// touch screen dokunulduğunda pozisyonlarını algılama 
    if (TS_State.touchDetected) { // dokunma algılandıysa yapılacaklar 
      
      x1 = TS_State.touchX[0];// x eksen bilgisi
      y1 = TS_State.touchY[0];// y eksen bilgisi 
      printf("Touch Detected x=%d y=%d\n", x1, y1);// serial monitörde astırma 

      BSP_LCD_SetTextColor(LCD_COLOR_RED);

      BSP_LCD_FillCircle(x1, y1, 5);// çember çizdirme 10 pixel çaplı 

      if (x1 < 210 && x1 > 160 && y1 < 180 && y1 > 130) {// bacgroun yazılan butona tıklandığında arka plan rengini değiştirme 
        wait_ms(100);
        printf("%d", renk);
        clear(renk);

      }
      if (x1 < 210 && x1 > 160 && y1 < 50 && y1) {// set clock yazısına basıldığında saat ayarlama gorsellerinin gelmesi 
        clear(renk - 1);
        saat_config = 2;
        wait_ms(100);
        BSP_LCD_SetFont( & Font24);
        BSP_LCD_DisplayStringAt(44, 75, (uint8_t * ) "^", LEFT_MODE);
        BSP_LCD_DisplayStringAt(105, 75, (uint8_t * )"^", LEFT_MODE);
        BSP_LCD_SetFont( & Font20);
        BSP_LCD_DisplayStringAt(44, 125, (uint8_t * )"v", LEFT_MODE);
        BSP_LCD_DisplayStringAt(105, 125, (uint8_t * )"v", LEFT_MODE);

      }
      if (saat_config == 2 && x1 < 60 && x1 > 30 && y1 < 90 && y1 > 55) {// saat arttırma butonu 

        wait_ms(100);
        saat = saat + 1;

      }
      if (saat_config == 2 && x1 < 120 && x1 > 90 && y1 < 90 && y1 > 55) {// dakika arttırma butonu 

        wait_ms(100);
        dakika = dakika + 1;

      }

      if (saat_config == 2 && x1 < 60 && x1 > 30 && y1 < 140 && y1 > 90) {// saat azaltma butonu 
        wait_ms(100);
        saat = saat - 1;
      }
      if (saat_config == 2 && x1 < 120 && x1 > 90 && y1 < 140 && y1 > 90) {//dakika azaltma butonu 

        wait_ms(100);
        dakika = dakika - 1;

      }

    }
  }
}