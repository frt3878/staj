const int pin = 32 ; // touch pin 
const int led = 12 ; // led yakmak için pin 
int value = 0 ; // pinden gelen değeri tutmak için 
void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(led,OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  value=analogRead(pin);
  if(value==0){digitalWrite(led,HIGH);
  Serial.println("Led on ");
  }
  else {digitalWrite(led,LOW);
  Serial.println("Led off ");}
  delay(500);
  // put your main code here, to run repeatedly:

}
