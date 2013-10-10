#define LED 13

String inputString="";

boolean led=0;

void setup(){
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
}

void loop(){
  if(inputString.startsWith("upali")) led=1;
  if(inputString.startsWith("ugasi")) led=0;
  if(inputString.startsWith("blink")) led=!led;
  
  digitalWrite(LED, led);
  delay(500);
}

void serialEvent() {
  inputString="";
  while(Serial.available()>0){
    inputString+=(char)Serial.read();
    delay(10);
  }
}
