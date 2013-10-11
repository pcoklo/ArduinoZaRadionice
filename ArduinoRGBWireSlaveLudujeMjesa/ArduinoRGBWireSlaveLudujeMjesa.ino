#include <Wire.h>

boolean good=false, led=0;

String inputString="";
String nullString="";
String tempString="";

const int r1Pin = 9,
          g1Pin = 10,
          b1Pin = 11;
          

int r1Int=0, g1Int=0, b1Int=0,
    newr1Int=0, newg1Int=0, newb1Int=0,
    r1Max=255, g1Max=255, b1Max=180,
    wait=5;

void setup(){
  Wire.begin(20);
  Wire.onReceive(reciveEvent);
  Wire.onRequest(requestEvent);
  
  pinMode(r1Pin, OUTPUT);
  pinMode(g1Pin, OUTPUT);
  pinMode(b1Pin, OUTPUT);
  pinMode(8, OUTPUT);
  
  analogWrite(r1Pin, 255); delay(150);
  analogWrite(r1Pin, 0); delay(150);
  analogWrite(g1Pin, 255); delay(150);
  analogWrite(g1Pin, 0); delay(150);
  analogWrite(b1Pin, 255); delay(150);
  analogWrite(b1Pin, 0); 
  
  pinMode(13, OUTPUT);
  digitalWrite(8,0);
}

void setRGB(){
  while(newr1Int!=r1Int||newg1Int!=g1Int||newb1Int!=b1Int){
    
    if(r1Int < newr1Int) r1Int++;
    if(r1Int > newr1Int) r1Int--;
    if(g1Int < newg1Int) g1Int++;
    if(g1Int > newg1Int) g1Int--;
    if(b1Int < newb1Int) b1Int++;
    if(b1Int > newb1Int) b1Int--;
        
    delay(wait);
    
    analogWrite(r1Pin, map(r1Int, 0, 255, 0, r1Max));
    analogWrite(g1Pin, map(g1Int, 0, 255, 0, g1Max));
    analogWrite(b1Pin, map(b1Int, 0, 255, 0, b1Max));
  }
}

void loop(){
  if (inputString.startsWith("#")){
    good=true;
    int tempIntArray[6];
    
    for(int i=0;i<6;i++){
      int tempInt=inputString.charAt(i+1);
      if(tempInt<=57) tempIntArray[i]=tempInt - 48;
      if(tempInt>64 && tempInt<71) tempIntArray[i]=tempInt - 55;
      if(tempInt>95 && tempInt<103) tempIntArray[i]=tempInt - 87;
    }
    newr1Int = tempIntArray[0]*16 + tempIntArray[1];
    newg1Int = tempIntArray[2]*16 + tempIntArray[3];
    newb1Int = tempIntArray[4]*16 + tempIntArray[5];
    wait=5;
    setRGB();
  }
  else if (inputString.startsWith("rgb:")){
    good=true;
    tempString=inputString.substring(inputString.indexOf(":")+1,inputString.indexOf(","));
    newr1Int=tempString.toInt();
    tempString=inputString.substring(inputString.indexOf(",")+1,inputString.lastIndexOf(","));
    newg1Int=tempString.toInt();
    tempString=inputString.substring(inputString.lastIndexOf(",")+1,inputString.length());
    newb1Int=tempString.toInt();
    wait=5;
    setRGB();
  }
  else if(inputString.startsWith("mjesaj")){
    good=true;
    wait=5;
    newr1Int=0;  newg1Int=0;  newb1Int=0  ;setRGB();//0
    newr1Int=255;newg1Int=0;  newb1Int=0  ;setRGB();//crvena
    newr1Int=255;newg1Int=255;newb1Int=0  ;setRGB();//crveno-zelena
    newr1Int=0;  newg1Int=255;newb1Int=0  ;setRGB();//zelena
    newr1Int=0;  newg1Int=255;newb1Int=255;setRGB();//zeleno-plava
    newr1Int=0;  newg1Int=0  ;newb1Int=255;setRGB();//plava
    newr1Int=255;newg1Int=0  ;newb1Int=255;setRGB();//plavo-crvena
    newr1Int=255;newg1Int=255;newb1Int=255;setRGB();//bijela
  }
  else if(inputString.startsWith("luduj")){
    good=true;
    wait=1;
    newr1Int=0;  newg1Int=0;  newb1Int=0  ;setRGB();//0
    newr1Int=255;newg1Int=0;  newb1Int=0  ;setRGB();//crvena
    newr1Int=0;  newg1Int=0;  newb1Int=0  ;setRGB();//0
    newr1Int=255;newg1Int=255;newb1Int=0  ;setRGB();//crveno-zelena
    newr1Int=0;  newg1Int=0;  newb1Int=0  ;setRGB();//0
    newr1Int=0;  newg1Int=255;newb1Int=0  ;setRGB();//zelena
    newr1Int=0;  newg1Int=0;  newb1Int=0  ;setRGB();//0
    newr1Int=0;  newg1Int=255;newb1Int=255;setRGB();//zeleno-plava
    newr1Int=0;  newg1Int=0;  newb1Int=0  ;setRGB();//0
    newr1Int=0;  newg1Int=0  ;newb1Int=255;setRGB();//plava
    newr1Int=0;  newg1Int=0;  newb1Int=0  ;setRGB();//0
    newr1Int=255;newg1Int=0  ;newb1Int=255;setRGB();//plavo-crvena
    newr1Int=0;  newg1Int=0;  newb1Int=0  ;setRGB();//0
    newr1Int=255;newg1Int=255;newb1Int=255;setRGB();//bijela
  }
  else good=false;
}
void reciveEvent(int x){
  inputString=nullString;
  while(Wire.available() > 0){
    char c = Wire.read();
    inputString += c;
  }
}
void requestEvent(){
  if(good)Wire.write("yes");
  else Wire.write("no");
}
