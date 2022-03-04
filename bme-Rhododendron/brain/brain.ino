#include <SoftwareSerial.h>
#define outputA 2
#define outputB 3
#define outputC 4
#define outputD 5
#define outputE 6
#define btInput 8
#define btOutput 9

SoftwareSerial bluetooth(btInput, btOutput);
char ch;
int targetPin = -1;

void test(){
  digitalWrite(outputA , LOW);
  delay(100);
  digitalWrite(outputA , HIGH);
  delay(100); 
}

void setup() {
  Serial.begin(9600);
  Serial.println("brain");
  bluetooth.begin(9600);
  pinMode(outputA , OUTPUT);
  pinMode(outputB , OUTPUT);
  pinMode(outputC , OUTPUT);
  pinMode(outputD , OUTPUT);
  pinMode(outputE , OUTPUT);
  digitalWrite(outputA , HIGH);
  digitalWrite(outputB , HIGH);
  digitalWrite(outputC , HIGH);
  digitalWrite(outputD , HIGH);
  digitalWrite(outputE , HIGH);
}

void loop() {
  if (bluetooth.available()) {
    ch = bluetooth.read();
    targetPin = -1;
    if (ch == 'A'){
      targetPin = outputA;
    }
    else if (ch == 'B'){
      targetPin = outputB;
    }
    else if (ch == 'C'){
      targetPin = outputC;
    }
    else if (ch == 'D'){
      targetPin = outputD;
    }
    else if (ch == 'E'){
      targetPin = outputE;
    }
    if (targetPin != -1){
      digitalWrite(targetPin , LOW );
      delay(100);
      digitalWrite(targetPin , HIGH);
    }
  }
}
