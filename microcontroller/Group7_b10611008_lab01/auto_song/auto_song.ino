#include "pitches.h"
int pins[] = {14 , 15 , 16 , 17 , 18 , 19 , 2};
int pianoPin = 3;
int melody[] = { NOTE_C4 , NOTE_D4 , NOTE_E4 , NOTE_F4 , NOTE_G4 , NOTE_A4 , NOTE_B4 };
int currentNote = -1;
double duration = 250;
int noteCount = 7;

int star[] = { 0 , 0 , 4,4 ,5 ,5 , 4 ,-1 ,  3 , 3,  2 , 2 , 1 , 1 , 0  };
int starLength = 15;

void setup() {
  for (int i = 0 ;i < noteCount ; i++){
    pinMode(pins[i] , INPUT);
  }
  Serial.begin(9600);
  for (int i = 0 ; i<starLength ; i++){
    if ( star[i] != -1 ){
      tone(pianoPin , melody[star[i]] , duration);
    }
    delay(duration * 1.3);
  }
}

void loop() {
}
