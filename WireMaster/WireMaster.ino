#include <Wire.h>
#include <RCSwitch.h>
#define LED 13

RCSwitch mySwitch = RCSwitch();

String inputString="";

void setup(){
  mySwitch.enableTransmit(4);
  Wire.begin();
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  Serial.println("pali gasi oda mario\nstar zelena plava\ntirkiz crvena zuta pink\nbijela off luduj mjesaj");
}

void loop(){}

void serialEvent() {
  inputString="";
  while(Serial.available()>0){
    inputString+=(char)Serial.read();
    delay(10);
  }
  if(inputString.startsWith("pali"))mySwitch.send("010101010100010101010001");
  if(inputString.startsWith("gasi"))mySwitch.send("010101010100010101010100");
  
  if(inputString.startsWith("oda"))mySwitch.send(150,8);
  if(inputString.startsWith("mario"))mySwitch.send(100,8);
  if(inputString.startsWith("star"))mySwitch.send(200,8);
  
  if(inputString.startsWith("plava")){
    Wire.beginTransmission(20);
    Wire.write("#0000FF");
    Wire.endTransmission();
  }
  if(inputString.startsWith("zelena")){
    Wire.beginTransmission(20);
    Wire.write("#00FF00");Wire.endTransmission();
  }
  if(inputString.startsWith("tirkiz")){
    Wire.beginTransmission(20);
    Wire.write("#00FFFF");Wire.endTransmission();
  }
  if(inputString.startsWith("crvena")){
    Wire.beginTransmission(20);
    Wire.write("#FF0000");Wire.endTransmission();
  }
  if(inputString.startsWith("pink")){
    Wire.beginTransmission(20);
    Wire.write("#FF00FF");Wire.endTransmission();
  }
  if(inputString.startsWith("zuta")){
    Wire.beginTransmission(20);
    Wire.write("#FFFF00");Wire.endTransmission();
  }
  if(inputString.startsWith("bijela")){
    Wire.beginTransmission(20);
    Wire.write("#FFFFFF");Wire.endTransmission();
  }
  if(inputString.startsWith("off")){
    Wire.beginTransmission(20);
    Wire.write("#000000");Wire.endTransmission();
  }
  if(inputString.startsWith("luduj")){
    Wire.beginTransmission(20);
    Wire.write("luduj");Wire.endTransmission();
  }
  if(inputString.startsWith("mjesaj")){
    Wire.beginTransmission(20);
    Wire.write("mjesaj");Wire.endTransmission();
  }
}
