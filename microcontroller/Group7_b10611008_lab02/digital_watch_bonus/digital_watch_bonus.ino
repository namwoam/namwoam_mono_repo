#define pinA 7
#define pinB 8
#define pinC 9
#define pinD 10
#define pinE 11
#define pinF 12
#define pinG 13

int clockSeconds = 0;
int countdownSeconds = 0;
double prevTime = 0;
double prevPress = 0;
double countdownAnchor =  0;
bool isCounting = false;
int currentMode = 0;
int outputPin[] = { 7 , 8 , 9 , 10 , 11 , 12 , 13 , 14 , 15 , 16 , 17};
int inputPin[] = {2 , 3 , 4};




void updateClock(){
  if ( millis() - prevTime >= 1000 ){
    clockSeconds +=1;
    prevTime = millis();
    Serial.println(clockSeconds);
  }
}

void clearNumber(int openLight , int closeLight){
  for(int i=7;i<14;i++){
    digitalWrite(i , closeLight);
  }
}
void showNumber(int n , int openLight , int closeLight){
  if (n ==0){
    //a b c d e f
    digitalWrite(pinA , openLight);
    digitalWrite(pinB , openLight);
    digitalWrite(pinC , openLight);
    digitalWrite(pinD , openLight);
    digitalWrite(pinE , openLight);
    digitalWrite(pinF , openLight);
  }
  else if (n==1){
    //b c
    digitalWrite(pinB , openLight);
    digitalWrite(pinC , openLight);
  }
  else if (n==2){
    //a b d e g
    digitalWrite(pinA , openLight);
    digitalWrite(pinB , openLight);
    digitalWrite(pinD , openLight);
    digitalWrite(pinE , openLight);
    digitalWrite(pinG , openLight);
  }
  else if (n==3){
    //a b c d g
    digitalWrite(pinA , openLight);
    digitalWrite(pinB , openLight);
    digitalWrite(pinC , openLight);
    digitalWrite(pinD , openLight);
    digitalWrite(pinG , openLight);
  }
  else if (n==4){
    //b c f g 
    digitalWrite(pinB , openLight);
    digitalWrite(pinC , openLight);
    digitalWrite(pinF , openLight);
    digitalWrite(pinG , openLight);
  }
  else if (n==5){
    //a c d f g
    digitalWrite(pinA , openLight);
    digitalWrite(pinC , openLight);
    digitalWrite(pinD , openLight);
    digitalWrite(pinF , openLight);
    digitalWrite(pinG , openLight);
  }
  else if (n==6){
    //c d e f g
    digitalWrite(pinC , openLight);
    digitalWrite(pinD , openLight);
    digitalWrite(pinE , openLight);
    digitalWrite(pinF , openLight);
    digitalWrite(pinG , openLight);
  }
  else if (n==7){
    //a b c
    digitalWrite(pinA , openLight);
    digitalWrite(pinB , openLight);
    digitalWrite(pinC , openLight);
  }
  else if (n==8){
    //a b c d e f g
    digitalWrite(pinA , openLight);
    digitalWrite(pinB , openLight);
    digitalWrite(pinC , openLight);
    digitalWrite(pinD , openLight);
    digitalWrite(pinE , openLight);
    digitalWrite(pinF , openLight);
    digitalWrite(pinG , openLight);
  }
  else if (n==9){
    //a b c f g
    digitalWrite(pinA , openLight);
    digitalWrite(pinB , openLight);
    digitalWrite(pinC , openLight);
    digitalWrite(pinF , openLight);
    digitalWrite(pinG , openLight);
  }
}

void showTime(int inputSeconds){
  
  int seconds = inputSeconds % 3600;
  int digits[] = {(seconds/60)/10 , (seconds/60)%10 , (seconds%60)/10 , (seconds%60)%10} ;
  //int digits[]={1 , 2 , 3,4};
  int pins[] = {14 , 15 , 16 , 17};
  for (int i=0;i<4 ; i++){
      digitalWrite(pins[i] , HIGH);
      clearNumber( 0, 1);
      showNumber(digits[i] , 0 , 1);
      clearNumber(0 , 1);
      digitalWrite(pins[i] , LOW);
  }
  
}

void setup() {
  clockSeconds = 0;
  prevTime = millis();
  prevPress = millis();
  currentMode = 1;
  Serial.begin(9600);
  for(int i=0;i<11 ; i++){
    pinMode(outputPin[i] , OUTPUT);
  }
  for(int i=0;i<3 ; i++){
    pinMode(inputPin[i] , INPUT);
  }
  for(int i=0;i<4;i++){
    digitalWrite(14+i , LOW);
  }
  countdownSeconds = 60;
}

void checkMode(){
  if (digitalRead(4) == 1 ){
    if (millis() - prevPress > 300){
      prevPress = millis();
      if (currentMode == 0){
        currentMode = 1 ;
      }
      else{
        currentMode = 0;
      }
    }
  }
}

void checkStart(){
  if (digitalRead(3) == 1 ){
    if (millis() - prevPress > 300){
      prevPress = millis();
      if (isCounting == false){
        countdownAnchor = millis();
      }
      isCounting = not isCounting;
    }
  }
}

void checkReset(){
  if ( digitalRead(2) == 1 and isCounting == false ){
    if (millis()-prevPress>300){
      countdownSeconds = 60;
    }
  }
}

void updateCount(){
  if (millis() - countdownAnchor >= 1000 and countdownSeconds > 0 ){
    countdownSeconds -= 1;
    countdownAnchor = millis();
  }
}

void loop() {
  updateClock();
  checkMode();
  if (currentMode == 0){
    showTime(clockSeconds);
  }
  else if (currentMode == 1){
    checkStart();
    showTime(countdownSeconds);
  }
  checkReset();
  if (isCounting){
    updateCount();
  }
}
