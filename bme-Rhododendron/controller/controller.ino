#define joyX A1
#define joyY A0
#define buttonA 8
#define buttonB 9
#define buttonC 10
#define buttonD 11
#define buttonE 12

int xValue , yValue;
int aValue , bValue , cValue , dValue , eValue;

void joystickInput(){
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  
  /*
  Serial.print("x:");
  Serial.print(xValue);
  Serial.print('\n');
  Serial.print("y:");
  Serial.print(yValue);
  Serial.print('\n');
  */
  if (xValue > 700){
    Serial.write('R');
  }
  else if (xValue < 300){
    Serial.write('L');
  }
  else if (yValue > 700){
    Serial.write('F');
  }
  else if (yValue < 300){
    Serial.write('X');
  }
}


void buttonInput(){
   aValue = digitalRead(buttonA);
   bValue = digitalRead(buttonB);
   cValue = digitalRead(buttonC);
   dValue = digitalRead(buttonD);
   eValue = digitalRead(buttonE);
   if (aValue == 1){
    Serial.print('A');
   }
   if (bValue == 1){
    Serial.print('B');
   }
   if (cValue == 1){
    Serial.print('C');
   }
   if (dValue == 1){
    Serial.print('D');
   }
   if (eValue == 1){
    Serial.print('E');
   }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonA , INPUT);
  pinMode(buttonB , INPUT);
  pinMode(buttonC , INPUT);
  pinMode(buttonD , INPUT);
  pinMode(buttonE , INPUT);  
}

void loop() {
  joystickInput();
  buttonInput();
  Serial.print('\n');
  delay(200);

}
