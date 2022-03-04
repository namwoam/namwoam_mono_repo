#define joyX A1
#define joyY A0
#define buttonA 8
#define buttonB 9
#define buttonC 10
#define buttonD 11
#define buttonE 12

int xValue , yValue;
int aValue , bValue , cValue , dValue , eValue;

void send(char ch){
  Serial.write(ch);
}

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
    send('R');
  }
  else if (xValue < 300){
    send('L');
  }
  else if (yValue > 700){
    send('F');
  }
  else if (yValue < 300){
    send('X');
  }
}


void buttonInput(){
   aValue = digitalRead(buttonA);
   bValue = digitalRead(buttonB);
   cValue = digitalRead(buttonC);
   dValue = digitalRead(buttonD);
   eValue = digitalRead(buttonE);
   if (aValue == 1){
    send('A');
   }
   if (bValue == 1){
    send('B');
   }
   if (cValue == 1){
    send('C');
   }
   if (dValue == 1){
    send('D');
   }
   if (eValue == 1){
    send('E');
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
  delay(100);

}
