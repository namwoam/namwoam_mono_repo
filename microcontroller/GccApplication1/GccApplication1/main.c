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
#include <avr/interrupt.h>


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

#define rightIR pinC4
#define leftIR pinC5
#define pinDMS pinC0

#define motorLeftA pinD6
#define motorLeftB pinD5
#define motorRightA pinB3
#define motorRightB pinD3

#define ledCount 3
#define pinBlink pinB1
#define pinReady pinB6

int pinLED[ledCount] = {pinB2 , pinD2 , pinD7} ; 
	

#define motorLeftSpeed 200
#define motorRightSpeed 200

int TimerOverflow = 0;

int frontDistance = 0;


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

/*
int analogRead(int pin){
	if (pin <= pinC5 && pin >= pinC0){
		int lowByte , highByte;
		ADMUX=(0b11000000 + pin - pinC0); // ref volt + channel
		ADCSRA = 0b10000111;
		ADCSRA|= (1<<ADEN);
		ADCSRA|=(1<<ADIF); // clear ADIF
		ADCSRA|=(1<<ADSC); 
		while((ADCSRA&(1<<ADIF))==0); // wait for ADC done
		lowByte=ADCL; // read low byte first
		highByte=ADCH;
		return highByte*256+lowByte;
	}
	else {
		return 0;
	}
	
}
*/

int readDistance()
{
	int adcHigh,adcLow;
	int voltage;
	ADCSRA|=(1<<ADIF); // clear ADIF
	ADCSRA|=(1<<ADSC); // start ADC
	while((ADCSRA&(1<<ADIF))==0); // wait for ADC done
	adcLow=ADCL;
	adcHigh=ADCH;
	voltage=adcHigh*256+adcLow;
	return voltage;
}

void setupSerial(){
	unsigned int BaudR=9600;
	unsigned int ubrr=(F_CPU/(BaudR*16UL))-1;
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

ISR(TIMER1_OVF_vect)
{
	TimerOverflow ++; // toggle PC5
}




void setup(){
	pinMode(motorLeftA , OUTPUT);
	pinMode(motorLeftB , OUTPUT);
	pinMode(motorRightA , OUTPUT);
	pinMode(motorRightB , OUTPUT);
	pinMode(pinDMS ,  INPUT);
	pinMode(rightIR , INPUT);
	pinMode(leftIR , INPUT);
	for (int i=0;i<ledCount ;i++){
		pinMode(pinLED[i] , OUTPUT);
		digitalWrite(pinLED[i] , HIGH);
	}
	pinMode(pinBlink , OUTPUT);
	digitalWrite(pinBlink , HIGH);
	pinMode(pinReady , OUTPUT);
	digitalWrite(pinReady , HIGH);
	setupSerial();
	sei();
	TIMSK1 = (1<<TOIE1);; // enable timer1 overflow interrupt and input
	TCCR1A = 0;
	ADCSRA=0b10000111; // enable + prescaler
	ADMUX=0b11000000; // ref volt + channel
	ADCSRA |= (1<<ADEN);
}

void stop(){
	analogWrite(motorRightA , 0);
	analogWrite(motorRightB , 0);
	analogWrite(motorLeftA , 0);
	analogWrite(motorLeftB , 0);
}

void turnRight(){
	analogWrite(motorRightA , 0);
	analogWrite(motorRightB , motorRightSpeed);
	analogWrite(motorLeftA , motorLeftSpeed);
	analogWrite(motorLeftB , 0);
	_delay_ms(280);
	stop();
}

void turnLeft(){
	analogWrite(motorRightA , motorRightSpeed);
	analogWrite(motorRightB , 0);
	analogWrite(motorLeftA , 0);
	analogWrite(motorLeftB , motorLeftSpeed);
	_delay_ms(280);
	stop();
}

void blink(int n){
	for (int i=0;i<n;i++){
		digitalWrite(pinBlink , LOW);
		_delay_ms(50);
		digitalWrite(pinBlink , HIGH);
		_delay_ms(50);
	}
}


int main(void)
{
	setup();
	/* Replace with your application code */
	while (1)
	{
		digitalWrite(pinReady , LOW);
		_delay_ms(50);
		digitalWrite(pinReady , HIGH);
		_delay_ms(50);
		char str[20];
		int dmsVoltage = readDistance();
		itoa( dmsVoltage , str , 10);
		strcat(str , "\n");
		printString(str);
		if (readDistance() > 90){
			digitalWrite(pinLED[1] , LOW);
		}
		else{
			digitalWrite(pinLED[1] , HIGH);
		}
		if (digitalRead(rightIR) == LOW){
			digitalWrite(pinLED[2] , LOW);
		}
		else{
			digitalWrite(pinLED[2] , HIGH);
		}
		if (digitalRead(leftIR) == LOW){
			digitalWrite(pinLED[0] , LOW);
		}
		else{
			digitalWrite(pinLED[0] , HIGH);
		}
		
		if(readDistance() < 90 && digitalRead(rightIR) == LOW ){
			// foward
			analogWrite(motorLeftA , motorLeftSpeed);
			analogWrite(motorLeftB , 0);
			analogWrite(motorRightA , motorRightSpeed);
			analogWrite(motorRightB , 0);
		}
		else if (readDistance() < 90 && digitalRead(rightIR) == HIGH){
			blink(1);
			_delay_ms(500);
			turnRight();
		}
		else if (readDistance()> 90 && digitalRead(leftIR) == LOW){
			blink(2);
			_delay_ms(500);
			turnLeft();
		}
		else if (readDistance() > 90 && digitalRead(leftIR) == HIGH ){
			blink(3);
			_delay_ms(500);
			turnLeft();
		}
	}
}


