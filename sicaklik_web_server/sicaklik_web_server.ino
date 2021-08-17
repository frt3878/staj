#include <WiFi.h>
#include <Wire.h>
#include <WebServer.h>


// SSID & Password
const char* ssid = "Yesil";  // wifi adi
const char* password = "password";  //wifi şifresi 
WebServer server(80); 
void web_server();
void button_pressed (); 
String veri = "1";
int16_t data[6];// okunacak veriler
void setup() {
  pinMode(4,OUTPUT);//output GPIO4 
  Serial.begin(115200);
  Wire.begin();// sensor haberleşme baslatma 
  Wire.beginTransmission(0x68);// cihaz adresi 0x68 
  Wire.write(0x6B);
  Wire.write(0); /* MPU-6050 çalıştırıldı */
  Wire.endTransmission(true);
  delay(800);
  /*--------------------------------------------------*/
  Serial.println("Baglanti Kuruluyor :  ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  // wifi baglanti kontrol 
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi baglanti kuruldu ");
  Serial.print(" IP: ");
  Serial.println(WiFi.localIP());  
  server.on("/", web_server);
  server.on("/buton",button_pressed);// server giris yapildiginda web_server fonksiyonunu baslat 
  server.begin();
  Serial.println("HTTP server baslatildi" );
   /*--------------------------------------------------*/
  delay(100); 
}
void loop() {
  server.handleClient();
  Wire.beginTransmission(0x68);
  /* I2C haberleşmesi yapılacak kart seçildi */
  Wire.write(0x3B); 
  /* 0x3B adresindeki register'a ulaşıldı */
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,14,true);
  /* 14 BYTE'lık veri istendi */
  
  data[0]=Wire.read()<<8|Wire.read();   
  data[1]=Wire.read()<<8|Wire.read(); 
  data[2] =Wire.read()<<8|Wire.read(); 
  data[3]=Wire.read()<<8|Wire.read(); // sıcaklık verisi 
  data[4]=Wire.read()<<8|Wire.read(); 
  data[5]=Wire.read()<<8|Wire.read();  
  data[6]=Wire.read()<<8|Wire.read();
  
  
  delay(4000);
}
String on_off="GPIO4 AC";
void web_server() {// 192.168.0.55 adresine gidine çağrılacak fonksiyon 
  /* html ve css kodları oluşturulan sitede yazılacak yazılar ve gönderilen sıcaklık bilgisi*/
  veri = String(data[3]/340.00+36.53);
  Serial.println("web weri");
  Serial.println(veri);
  String HTML = "<!DOCTYPE html>\   
  <html>\
  <head>\
  <meta http-equiv='refresh' content='10;'/>\
    <style>\
     body {background-image: url('https://yt3.ggpht.com/ytc/AKedOLSX-RJDCoNqSNpEG3NGJ3D-EruR8hDY7KYLHO1BoQ=s900-c-k-c0x00ffffff-no-rj');\
    background-repeat: no-repeat;\
    background-attachment: fixed;\
    background-size: cover;\
    background-size: 100% 100%;\}\
    .button { background-color: grey ;\ 
    border-radius: 15%;\
    color: black;\
    padding: 10px 10px;\
    margin:  15px 15px;\
    text-decoration: none ;\
    font-size: 30px;\
    margin-left: 15px;\
    }\
    .veri {color: black;\}\
   .sicaklik { text-align: center;\ 
   color:black;\
   font-size: 50px;\}\
    </style>\
  </head>\
  <body >\
  <p \class = sicaklik >  ESP32 WEB SERVER </p>   \
  <p \class = sicaklik > Anlik Oda Sicakligi :  <b \class = veri >" +veri+ " &#x2103 .</b></p>   \
  <p>- </p>   \
  <p>- </p>   \
  <p>- </p>   \
  <p>- </p>   \
  <p>- </p>   \
  <p>- </p>   \
  <p><center>  <a href=\"/buton \" \class= button >"+ on_off +"</a></center></p>\
  <p>- </p>   \
  <p\class = sicaklik>-</p>   \
  <p><center> <a href=\"/ \"  class= button>Sayfayi yenile   </a></center></p>\
  </body>\
  </html>";
  server.send(200, "text/html", HTML);
}
int sayac=0;
void button_pressed (){
    
    
   veri = String(data[3]/340.00+36.53);
  Serial.println("sayac weri");
  Serial.println(sayac);
  if(sayac==0){
  digitalWrite(4,HIGH);
  on_off="GPIO4 Kapa";
  sayac=1;
  }
   else{
  digitalWrite(4,LOW);
  sayac=0;
  on_off="GPIO4 AC";
  }
     String HTML = "<!DOCTYPE html>\   
  <html>\
  <head>\
    <style>\
     body {background-image: url('https://yt3.ggpht.com/ytc/AKedOLSX-RJDCoNqSNpEG3NGJ3D-EruR8hDY7KYLHO1BoQ=s900-c-k-c0x00ffffff-no-rj');\
    background-repeat: no-repeat;\
    background-attachment: fixed;\
    background-size: cover;\
    background-size: 100% 100%;\}\
    .button { background-color: grey ;\ 
    border-radius: 15%;\
    color: black;\
    padding: 10px 10px;\
    margin:  15px 15px;\
    text-decoration: none ;\
    font-size: 30px;\
    margin-left: 15px;\
    }\
    .veri {color: black;\}\
   .sicaklik { text-align: center;\ 
   color:black;\
   font-size: 50px;\}\
    </style>\
  </head>\
  <body >\
  <p \class = sicaklik >  ESP32 WEB SERVER </p>   \
  <p \class = sicaklik > Anlik Oda Sicakligi :  <b \class = veri >" +veri+ " &#x2103 .</b></p>   \
  <p>- </p>   \
  <p>- </p>   \
  <p>- </p>   \
  <p>- </p>   \
  <p>- </p>   \
  <p>- </p>   \
  <p><center>  <a href=\"/buton \" \class= button >"+ on_off +"</a></center></p>\
  <p>- </p>   \
  <p\class = sicaklik>-</p>   \
  <p><center> <a href=\"/ \"  class= button>Sayfayi yenile   </a></center></p>\
  </body>\
  </html>";
  server.send(200, "text/html", HTML);
}
  
