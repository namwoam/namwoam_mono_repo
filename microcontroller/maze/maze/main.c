/*
 * maze.c
 *
 * Created: 5/4/2022 4:59:10 PM
 * Author : USER
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

// General library
#define INPUT 0
#define OUTPUT 1
#define HIGH 1
#define LOW 0

#define pinD0 0
#define pinD1 1
#define pinD2 2
#define pinD3 3
#define pinD4 4
#define pinD5 5
#define pinD6 6
#define pinD7 7

#define pinC0 8
#define pinC1 9
#define pinC2 10
#define pinC3 11
#define pinC4 12
#define pinC5 13
#define pinC6 14

#define pinB0 15
#define pinB1 16
#define pinB2 17
#define pinB3 18
#define pinB4 19
#define pinB5 20
#define pinB6 21
#define pinB7 22

#define sensorCount 3

int sensorValues[sensorCount];
int sensorPins[sensorCount] = { pinC5 , pinC4 , pinC0};

int ledPins[sensorCount] = 	{pinB0 , pinD2 , pinD7 };

#define motorLeftA pinD6
#define motorLeftB pinD5
#define motorRightA pinB3
#define motorRightB pinD3

#define motorLeft_maxSpeed 255
#define motorRight_maxSpeed 255


void digitalWrite(int pin , int n){
	// n=0 LOW
	// n=1 HIGH
	if (n==0){
		if  (pin >= 0 && pin <= 7){
			PORTD = PORTD & ~(1<<pin);
		}
		else if (pin >= 8 && pin <= 14 ){
			PORTC = PORTC & ~(1<<(pin-8));
		}
		else if (pin >=15 && pin <= 22 ){
			PORTB = PORTB & ~(1<<(pin-15));
		}
	}
	else if ( n == 1){
		if (pin >=0 && pin <= 7 ){
			PORTD = PORTD | (1<<pin);
		}
		else if (pin >=8 && pin <= 14 ){
			PORTC = PORTC | (1<<(pin - 8));
		}
		else if (pin >=15 && pin <= 22 ){
			PORTB = PORTB | (1<<(pin - 15));
		}
	}
	return ;
}

void pinMode(int pin , int n){
	// n=0 INPUT
	// n=1 OUTPUT
	if (n==0){
		if  (pin >= 0 && pin <= 7){
			DDRD = DDRD & ~(1<<pin);
			PORTD = PORTD | (1<<pin);
		}
		else if (pin >= 8 && pin <= 14 ){
			DDRC = DDRC & ~(1<<(pin-8));
			PORTC = PORTC | (1<<(pin-8));
		}
		else if (pin >=15 && pin <= 22){
			DDRB = DDRB & ~(1<<(pin-15));
			PORTB = PORTB | (1<<(pin-15));
		}
	}
	else if ( n == 1){
		if (pin >=0 && pin <= 7 ){
			DDRD = DDRD | (1<<pin);
		}
		else if (pin >=8 && pin <= 14 ){
			DDRC = DDRC | (1<<(pin - 8));
		}
		else if (pin >=15 && pin <= 22){
			DDRB = DDRB | (1<<(pin - 15));
		}
	}
	return ;
}

int digitalRead(int pin){
	int signal = 0;
	// return 0 if LOW , 1 if HIGH
	if (pin >=0 && pin <=7){
		signal = ((PIND >> (pin)) & 1);
	}
	else if (pin >= 8 && pin <= 14){
		signal = ((PINC >> (pin -8 )) & 1);
	}
	else if (pin >=15 && pin <= 22){
		signal = ((PINB >> (pin -15 )) & 1);
	}
	if (signal == 1){
		return 1;
	}
	else {
		return 0;
	}
}

void analogWrite(int pin , int val){
	// only support OC0A/B OC2A/B
	val %= 256;
	if (pin == pinD5 || pin == pinD6){
		TCCR0A=0b10100011;
		TCCR0B=0b00000001;
		if (pin == pinD5){
			OCR0B = val;
		}
		else if (pin == pinD6) {
			OCR0A = val;
		}
	}
	else if (pin == pinD3 || pin == pinB3){
		TCCR2A=0b10100011;
		TCCR2B=0b00000001;
		if (pin == pinD3){
			OCR2B = val;
		}
		else if (pin == pinB3) {
			OCR2A = val;
		}
	}
	return ;
}

int analogRead(int pin){
	if (pin <= pinC5 && pin >= pinC0){
		int lowByte , highByte;
		ADCSRA=0b10000111; // enable + prescaler
		ADMUX=(0b11000000 + pin - pinC0); // ref volt + channel
		ADCSRA|=(1<<ADIF); // clear ADIF
		ADCSRA|=(1<<ADSC); // start ADC
		while((ADCSRA&(1<<ADIF))==0); // wait for ADC done
		lowByte=ADCL; // read low byte first
		highByte=ADCH;
		return highByte*256+lowByte;
	}
	else {
		return 0;
	}
	
}

void setupSerial(){
	unsigned int BaudR=9600;
	unsigned int ubrr=(F_CPU/(BaudR*16UL))-1;
	CLKPR=0b10000000;
	CLKPR=0b00000000;
	UBRR0H=(unsigned char)(ubrr>>8);
	UBRR0L=(unsigned char)ubrr;
	UCSR0B=(1<<TXEN0);
	UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);
}

void printString(char* StringPtr){
	while(*StringPtr != 0x00){
		while(!(UCSR0A& (1<<UDRE0)));
		UDR0=*StringPtr;
		StringPtr++;
	}
}

void readFromDMSSensor()
{
	int voltage;
	voltage=analogRead(pinC5);
	sensorValues[0]=voltage;
	char Buffer[20];
	char *DMSvalue =  itoa(voltage, Buffer, 10);
	strcat(DMSvalue, "\n");
	printString(DMSvalue);
}

void readFromIRSensor(){
	for (int i=1;i<sensorCount;i++){
		sensorValues[i] = analogRead(sensorPins[i]);
	char Buffer[20];
	char *IRvalue =  itoa(sensorValues[i], Buffer, 10);
	strcat(IRvalue, "\n");
	printString(IRvalue);
	}
	
}



void setup(){
	for (int i=0;i<sensorCount;i++){
		pinMode(sensorPins[i] , INPUT);
		pinMode(ledPins[i] , OUTPUT);
	}
	pinMode(motorLeftA , OUTPUT);
	pinMode(motorLeftB , OUTPUT);
	pinMode(motorRightA , OUTPUT);
	pinMode(motorRightB , OUTPUT);
	setupSerial();
}

void updateSpeed(int speedLeft , int speedRight){
	analogWrite(motorLeftA , speedLeft);
	analogWrite(motorLeftB , 0);
	analogWrite(motorRightA , speedRight);
	analogWrite(motorRightB , 0);
	return;
}

int isForward()
{
	if(sensorValues[0] > 100)
		return 0;
	else if(sensorValues[0]<=100)
		return 1;
	else
		return 2;
}

int isRight()
{
	if(sensorValues[1] > 100)
		return 0;
	else if(sensorValues[1]<=100)
		return 1;
	else
		return 2;
}

int isLeft()
{
	if(sensorValues[2] > 100)
		return 0;
	else if(sensorValues[2]<=100)
		return 1;
	else
		return 2;
}

int direction()
{
	if(isForward()==0 && isRight()==1)
		return 1; //forward
	else if(isForward()==0 && isRight()==0)
		return 2; //turn right
	else if (isForward()==1 && isRight()==1)
		return 3; //turn left
	else
		return 4;
}

void updateLed(){
	for (int i=0;i<sensorCount;i++){
		digitalWrite(ledPins[i] , LOW);
		if (direction()==i+1){
			digitalWrite(ledPins[i] , HIGH);
		}
	}
}
int main(void)
{
	setup();
	/* Replace with your application code */
	while (1)
	{
		readFromDMSSensor();
		readFromIRSensor();
		updateLed();
		if (direction()==1)
			updateSpeed(motorRight_maxSpeed,motorLeft_maxSpeed);
		else if (direction()==2)
			updateSpeed(motorLeft_maxSpeed/3 , motorLeft_maxSpeed);
		else if (direction()==3)
			updateSpeed(motorRight_maxSpeed , motorLeft_maxSpeed/3);
		
	}
}


