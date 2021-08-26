import bluetooth # pybluez kütüphanesinden bluetooth 
import playsound # sesli iletişim için kütüphaneler 
import pyaudio
import speech_recognition as sr



r=sr.Recognizer()
mic=sr.Microphone()

print("Bluetooth cihazları taranıyor ...")

devices = bluetooth.discover_devices(lookup_names = True, lookup_class = True)

number_of_devices = len(devices)

print(number_of_devices,"cihaz bulundu.")

for addr, name, device_class in devices:

     print("\n")

     print("Device:")

     print("Device Name: %s" % (name))# cihaz adı bastırma

     print("Device MAC Address: %s" % (addr)) # cihaz mac adres

     print("\n")


bd_addr = "30:AE:A4:99:4D:B6"   # esp32 mac adress

port = 1

s=bluetooth.BluetoothSocket( bluetooth.RFCOMM )# bağlantı tipi
s.connect((bd_addr, port))#port  numarası ve bağlanma
print("Bağlantı başarılı sesli komut için 1. Yazmak için 2  ")
select = input()
select=int(select)# stringi integer a dönüştürme
while(1):
    if(select==1):# sesli komut ile yönetme 
        print("sesli komut seçildi")
        with mic as kaynak:
            ses=r.listen(kaynak)# mikrafonden gelen sesi dinle 
            text=r.recognize_google(ses,language="Tr-tr")# ses dosyasını çevrimiçi google yardımı ile texte çevirme
        if (text == "çıkış"):
            s.send("kapat")# çıkış denildiğinde pwm i kapatma
            break
        print(text)
        s.send(text + "\n")  # değer yollama

    if (select == 2):# yazı ile yönetme 
        print("Yazı seçildi")
        x=input()# klavyeden veri alma
        s.send(x + "\n")# \n konmasının sebebi arduino ide \n komutu geldiğinde cümlenin bittiği anlamına gelmekte
        if(x=="exit") :
            break


s.close() # bluetooth bağlantısı kapama