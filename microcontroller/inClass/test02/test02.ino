#define buttonPin 2
#define ledPin 13


void setup() {
  pinMode(buttonPin , INPUT);
  pinMode(ledPin , OUTPUT);
  Serial.begin(9600);
  buttonCount = 0;
}

void loop() {
  if (digitalRead(buttonPin) == 1){
    Serial.println("Pressed");
    pressed = true;
    buttonCount +=1;
  }
  else{
    Serial.println("not Pressed");
    pressed = false;
  }
  digitalWrite(ledPin , HIGH);
  if (pressed == true){
    delay(pressedTime);
  }
  else{
    delay(releasedTime);
  }
  digitalWrite(ledPin , LOW);
  if (pressed == true){
    delay(pressedTime);
  }
  else{
    delay(releasedTime);
  }
}
