//libraries
#include <unistep.h>

//stepper
unistep stepper1(7,8,9,10,4096,900);
int incomingByte;
boolean left = false;
boolean right = false;

//light sensor

int photocellPin = 0;     
int photocellReading;     
int LEDpin = 11;          
int LEDbrightness;       

///speaker
int photocell1Pin = 1; 
int SPEAKER = 5;
int photocell1Reading; 
char notes[ ] = "CDEFGABC"; 
//              C D E F G A B C 
int beats[ ] = { 2,2,2,2,2,2,2,2};
int tempo = 175;
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(SPEAKER, HIGH);
    delayMicroseconds(tone);
    digitalWrite(SPEAKER, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B', };
  char tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};

  for (int i = 0; i < sizeof(tones); i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }

}


void setup(void)
{
  //stepper
Serial.begin(9600);
pinMode(3, INPUT);
pinMode(4, INPUT);

//speaker
pinMode(SPEAKER, OUTPUT);

}

void loop(void){

 //stepper
           if(digitalRead(3)==HIGH && left == false){
           Serial.println("left");
           left = true;
           stepper1.moves(4096,1);
    
    
            }
            if(digitalRead(4)==HIGH && right == false){
              right = true;
               Serial.println("right");
              stepper1.moves(4096,0);
              
             
              
            }
          
            if(digitalRead(3)==LOW){
              left = false;
            }
          
             if(digitalRead(4)==LOW){
              right = false;
delay(10);

}
  //light sensor

      photocellReading = analogRead(photocellPin);  
 
  Serial.print("Analog reading = ");
  Serial.println(photocellReading);    
 
   photocellReading = 1023 - photocellReading;
 
  LEDbrightness = map(photocellReading, 0, 1023, 0, 255);
  analogWrite(LEDpin, LEDbrightness);
 
  delay(100);

  //speaker
    
photocell1Reading = analogRead(photocell1Pin);

 

Serial.print("Analog reading = ");

Serial.print(photocell1Reading); 

 

if (photocell1Reading < 90) {

Serial.println(" – Dark");
Serial.println(" – Bright");

//speaker
for (int i = 0; i < sizeof(notes); i++) {  
playNote(notes[i], beats[i] * tempo);
delay(tempo / 2); 
  if (analogRead(photocell1Pin)>51) { break; }

  }
} else if (photocell1Reading < 200) {

Serial.println(" – Dim");

} else if (photocell1Reading < 500) {

Serial.println(" – Light");

} else if (photocell1Reading < 800) {


} else {

Serial.println(" – Very bright");

}


delay(1000);

}

