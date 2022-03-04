#define pinA 7
#define pinB 8
#define pinC 9
#define pinD 10
#define pinE 11
#define pinF 12
#define pinG 13

int clockSeconds = 0;
double prevTime = 0;
int currentMode = 0;
int outputPin[] = { 7 , 8 , 9 , 10 , 11 , 12 , 13 , 14 , 15 , 16 , 17};
int inputPin[] = {}; 



void updateClock(){
  if ( millis() - prevTime >= 100 ){
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
  int digits[] = {(seconds/60)/10 , (seconds/60)%10 , (seconds%60)/10 , (clockSeconds%60)%10} ;
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
  currentMode = 0;
  Serial.begin(9600);
  for(int i=0;i<11 ; i++){
    pinMode(outputPin[i] , OUTPUT);
  }
  for(int i=0;i<4;i++){
    digitalWrite(14+i , LOW);
  }
}

void loop() {
  updateClock();
  if (currentMode == 0){
    showTime(clockSeconds);
  }
  

}
