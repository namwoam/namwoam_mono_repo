/*

  Switch statement with serial input

  Demonstrates the use of a switch statement. The switch statement allows you

  to choose from among a set of discrete values of a variable. It's like a

  series of if statements.

  To see this sketch in action, open the Serial monitor and send any character.

  The characters a, b, c, d, and e, will turn on LEDs. Any other character will

  turn the LEDs off.

  The circuit:

  - five LEDs attached to digital pins 2 through 6 through 220 ohm resistors

  created 1 Jul 2009

  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cchttps://www.arduino.cc/en/Tutorial/SwitchCase2

*/

int pin  = 0;

void setup() {

  // initialize serial communication:

  Serial.begin(9600);

  // initialize the LED pins:

  for (int thisPin = 2; thisPin < 7; thisPin++) {

    pinMode(thisPin, OUTPUT);

  }
}

void loop() {
  for(int i=0;i<8;i++){
    
    if (i<5){
      pin = i+2;
    }
    else{
      pin = (10-i);
    }
    digitalWrite(pin , HIGH);
    delay(100);
    digitalWrite(pin , LOW);
  }
}
