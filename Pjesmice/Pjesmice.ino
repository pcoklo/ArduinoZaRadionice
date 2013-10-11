//pjesmice
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
int value;

int ledPin = 13;
 
int speakerPin = 11;

int length = 295;
char notes[] = "EE E CE G  g  C  g e  a b ia gEGA FG E CDb C  g e  a b ia gEGA FG E CDb  GNFR E uaC aCD GNFR E 1 11   GNFR E uaC aCD L  D C   CC C CD EC ag  CC C CDE  CC C CD EC ag  EE E CE G  g  C  g e  a b ia gEGA FG E CDb C  g e  a b ia gEGA FG E CDb EC g u aF Fa  bAAAGFEC ag  EC g u aF Fa  bF FFEDCe ec  "; // a space represents a rest
float beats[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, //Page 1
                2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 4, //Page 2
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, //Page4
                1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, //Page 5
                1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1.3, 1.3, 1.3, 1, 1, 1, 1, 1, 1, 2 }; //Page 6
int tempo = 95;
void playTone(int ton1, int duration) {
  for (long i = 0; i < duration * 1000L; i += ton1) {
    tone(speakerPin, ton1);
    delayMicroseconds(ton1);
  }
  noTone(speakerPin);
}
void playNote(char note, int duration) {
  char names[] = { ' ',  '!', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D', 'E', 'F', 'G', 'A', 'B', 'i', 'N', 'R', 'u',  '1', 'L', 'k'}; // [i = b flat] [N = G flat] [R = D#] [u = g#] [1 = C oct. 5] [L = E flat]
  int tones[] =  {   0, 1046, 138, 146, 155, 164, 174, 184, 195, 207, 220, 233, 246, 261, 293, 329, 349, 391, 440, 493, 523, 587, 659, 698, 783, 880, 987, 466, 740, 622, 415, 1046, 622u, 227};
  
  for (int i = 0; i < 34; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
 
#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880
 
void setup() 	 
{
  pinMode(5,1);digitalWrite(5,1);
  pinMode(2,1);digitalWrite(2,0);	 
  pinMode(ledPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  mySwitch.enableReceive(1);
} 	 
  	 
void loop(){
  if (mySwitch.available()) {
    value = mySwitch.getReceivedValue();
    mySwitch.resetAvailable();
  }
  if (value==200){
    digitalWrite(4,0);
    value=0;
    march();
  }
  if (value==150){
    digitalWrite(4,0);
    value=0;
    oda();
  }
  
  if (value==100){
    value=0;
    for (int i = 0; i < length; i++) {
      if (notes[i] == ' ') {
        delay(beats[i] * tempo);
      } else {
        playNote(notes[i], beats[i] * tempo);
      }
      delay(tempo / 2); 
    }
  }
  
} 	 
  	 
void beep (int frequencyInHertz, long timeInMilliseconds)
{ 
    digitalWrite(ledPin, HIGH);    
    int x; 	 
    long delayAmount = (long)(1000000/frequencyInHertz);
    long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
    for (x=0;x<loopTime;x++) 	 
    { 	 
        digitalWrite(speakerPin,HIGH);
        delayMicroseconds(delayAmount);
        digitalWrite(speakerPin,LOW);
        delayMicroseconds(delayAmount);
    } 	 
    
    digitalWrite(ledPin, LOW);
    delay(20);
} 	 
  	 
void march(){
  beep(a, 500); 
  beep(a, 500);     
  beep(a, 500); 
  beep(f, 350); 
  beep(cH, 150);
 
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 1000);
    
  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);    
  beep(fH, 350); 
  beep(cH, 150);

  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 1000);
  //second bit...
  
  beep(aH, 500);
  beep(a, 350); 
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 250); 
  beep(gH, 250);
    
  beep(fSH, 125);
  beep(fH, 125);    
  beep(fSH, 250);
  delay(250);
  beep(aS, 250);    
  beep(dSH, 500);  
  beep(dH, 250);  
  beep(cSH, 250);  
  //start of the interesting bit
  
  beep(cH, 125);  
  beep(b, 125);  
  beep(cH, 250);      
  delay(250);
  beep(f, 125);  
  beep(gS, 500);  
  beep(f, 375);  
  beep(a, 125); 
  
  beep(cH, 500); 
  beep(a, 375);  
  beep(cH, 125); 
  beep(eH, 1000); 
  //more interesting stuff (this doesn't quite get it right somehow)
  
  beep(aH, 500);
  beep(a, 350); 
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 250); 
  beep(gH, 250);
  
  beep(fSH, 125);
  beep(fH, 125);    
  beep(fSH, 250);
  delay(250);
  beep(aS, 250);    
  beep(dSH, 500);  
  beep(dH, 250);  
  beep(cSH, 250);  
  //repeat... repeat
  
  beep(cH, 125);  
  beep(b, 125);  
  beep(cH, 250);      
  delay(250);
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 375);  
  beep(cH, 125); 
         
  beep(a, 500);            
  beep(f, 375);            
  beep(c, 125);            
  beep(a, 1000);       
  //and we're done \ó/    
}

void oda(){
  beep(e, 500); 
  beep(e, 500);
  beep(f, 500);
  beep(g, 500);
  
  beep(g, 500);
  beep(f, 500);
  beep(e, 500);
  beep(d, 500);
  
  beep(c, 500);
  beep(c, 500);
  beep(d, 500);
  beep(e, 500);
  
  beep(e, 750);
  beep(d, 250);
  beep(d, 1000);
  //lalal
  beep(e, 500); 
  beep(e, 500);
  beep(f, 500);
  beep(g, 500);
  
  beep(g, 500);
  beep(f, 500);
  beep(e, 500);
  beep(d, 500);
  
  beep(c, 500);
  beep(c, 500);
  beep(d, 500);
  beep(e, 500);
  
  beep(d, 750);
  beep(c, 250);
  beep(c, 1000);
  //lalala*/
  beep(d, 500);
  beep(d, 500);
  beep(e, 500);
  beep(c, 500);
  
  beep(d, 500);
  beep(e, 250);
  beep(f, 250);
  beep(e, 500);
  beep(c, 500);
  
  beep(d, 500);
  beep(e, 250);
  beep(f, 250);
  beep(e, 500);
  beep(d, 500);
  
  beep(c, 500);
  beep(d, 500);
  beep(200, 750);
  delay(50);
  //lalala
  beep(e, 500); 
  beep(e, 500);
  beep(f, 500);
  beep(g, 500);
  
  beep(g, 500);
  beep(f, 500);
  beep(e, 500);
  beep(d, 500);
  
  beep(c, 500);
  beep(c, 500);
  beep(d, 500);
  beep(e, 500);
  
  beep(d, 750);
  beep(c, 250);
  beep(c, 1000);
  //lalala*/
}/**/
