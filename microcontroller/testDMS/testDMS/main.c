/*
* GccApplication6.c
*
* Created: 2022/4/6 下午 04:33:28
* Author : claire
*/

#define INPUT 0
#define OUTPUT 1
#define HIGH 1
#define LOW 0

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

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

int readDistance()
{
	int adcHigh,adcLow;
	int voltage;
	int distance;
	ADCSRA|=(1<<ADIF); // clear ADIF
	ADCSRA|=(1<<ADSC); // start ADC
	while((ADCSRA&(1<<ADIF))==0); // wait for ADC done
	adcLow=ADCL;
	adcHigh=ADCH;
	voltage=adcHigh*256+adcLow;
	if (voltage <= 1023 && voltage >= 1000){
		distance = 5*(1023-voltage)/(23)+20;
	}
	else if (voltage >= 890 && voltage <= 1000){
		distance = 5*(1000-voltage)/(110)+25;
	}
	else if (voltage>=700 && voltage <= 890){
		distance = 10*(890-voltage)/(120)+30;
	}
	else if (voltage >= 620 && voltage <= 700){
		distance = 10*(700-voltage)/(80)+40;
	}
	else {
		distance = 0;
	}
	return voltage;
}

void USART_putstring(char* StringPtr)
{
	while(*StringPtr != 0x00){
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = *StringPtr;
		StringPtr++;
	}
}
void print()
{
	float sumVal = 0;
	char Buffer[8];
	for(int i = 0; i < 10; i++){
		sumVal += (float)readDistance();
	}
	sumVal /= 10; //mean of 10 readings
	char *intStr = itoa((int)sumVal, Buffer, 10);
	strcat(intStr, "\n");
	USART_putstring(intStr);
	char string[] = "Hello World\n";
	USART_putstring(string);
	
}

void displayCharacter1(char ch){
	if (ch == '1'){
		digitalWrite(10 , LOW);
		digitalWrite(2 , LOW);
	}
	else if (ch == '2'){
		digitalWrite(9 , LOW);
		digitalWrite(10 , LOW);
		digitalWrite(6 , LOW);
		digitalWrite(4 , LOW);
		digitalWrite(3 , LOW);
	}
	else if (ch == '3'){
		digitalWrite(9 , LOW);
		digitalWrite(10 , LOW);
		digitalWrite(6 , LOW);
		digitalWrite(2 , LOW);
		digitalWrite(3 , LOW);
	}
	else if (ch == '4'){
		digitalWrite(5 , LOW);
		digitalWrite(6 , LOW);
		digitalWrite(10 , LOW);
		digitalWrite(2 , LOW);
	}
	else if (ch == '5'){
		digitalWrite(9 , LOW);
		digitalWrite(5 , LOW);
		digitalWrite(6 , LOW);
		digitalWrite(2 , LOW);
		digitalWrite(3 , LOW);
	}
	else if (ch == '6'){
		digitalWrite(9 , LOW);
		digitalWrite(5 , LOW);
		digitalWrite(6 , LOW);
		digitalWrite(2 , LOW);
		digitalWrite(4 , LOW);
		digitalWrite(3 , LOW);
	}
	else if (ch == '7'){
		digitalWrite(5 , LOW);
		digitalWrite(9 , LOW);
		digitalWrite(10 , LOW);
		digitalWrite(2 , LOW);
	}
	else if (ch == '8'){
		digitalWrite(9 , LOW);
		digitalWrite(10 , LOW);
		digitalWrite(2 , LOW);
		digitalWrite(3 , LOW);
		digitalWrite(4 , LOW);
		digitalWrite(5 , LOW);
		digitalWrite(6 , LOW);
	}
	else if (ch == '9'){
		digitalWrite(9 , LOW);
		digitalWrite(10 , LOW);
		digitalWrite(2 , LOW);
		digitalWrite(3 , LOW);
		digitalWrite(5 , LOW);
		digitalWrite(6 , LOW);
	}
	else if (ch == '0'){
		digitalWrite(9 , LOW);
		digitalWrite(10 , LOW);
		digitalWrite(2 , LOW);
		digitalWrite(3 , LOW);
		digitalWrite(4 , LOW);
		digitalWrite(5 , LOW);
	}
	else if (ch == '@'){
		digitalWrite(9 , HIGH);
		digitalWrite(10 , HIGH);
		digitalWrite(2 , HIGH);
		digitalWrite(3 , HIGH);
		digitalWrite(4 , HIGH);
		digitalWrite(5 , HIGH);
		digitalWrite(6 , HIGH);
	}
	return ;
}

void displayCharacter2(char ch){
	if (ch == '1'){
		digitalWrite(16 , LOW);
		digitalWrite(17 , LOW);
	}
	else if (ch == '2'){
		digitalWrite(15 , LOW);
		digitalWrite(16 , LOW);
		digitalWrite(13 , LOW);
		digitalWrite(19 , LOW);
		digitalWrite(18 , LOW);
	}
	else if (ch == '3'){
		digitalWrite(15 , LOW);
		digitalWrite(16 , LOW);
		digitalWrite(13 , LOW);
		digitalWrite(17 , LOW);
		digitalWrite(18, LOW);
	}
	else if (ch == '4'){
		digitalWrite(20 , LOW);
		digitalWrite(13 , LOW);
		digitalWrite(16 , LOW);
		digitalWrite(17 , LOW);
	}
	else if (ch == '5'){
		digitalWrite(15 , LOW);
		digitalWrite(20 , LOW);
		digitalWrite(13 , LOW);
		digitalWrite(17 , LOW);
		digitalWrite(18 , LOW);
	}
	else if (ch == '6'){
		digitalWrite(15 , LOW);
		digitalWrite(20 , LOW);
		digitalWrite(13 , LOW);
		digitalWrite(17 , LOW);
		digitalWrite(19 , LOW);
		digitalWrite(18 , LOW);
	}
	else if (ch == '7'){
		digitalWrite(20 , LOW);
		digitalWrite(15 , LOW);
		digitalWrite(16 , LOW);
		digitalWrite(17 , LOW);
	}
	else if (ch == '8'){
		digitalWrite(15 , LOW);
		digitalWrite(16 , LOW);
		digitalWrite(17 , LOW);
		digitalWrite(18 , LOW);
		digitalWrite(19 , LOW);
		digitalWrite(20 , LOW);
		digitalWrite(13 , LOW);
	}
	else if (ch == '9'){
		digitalWrite(15 , LOW);
		digitalWrite(16 , LOW);
		digitalWrite(17 , LOW);
		digitalWrite(18 , LOW);
		digitalWrite(20, LOW);
		digitalWrite(13 , LOW);
	}
	else if (ch == '0'){
		digitalWrite(15 , LOW);
		digitalWrite(16 , LOW);
		digitalWrite(17 , LOW);
		digitalWrite(18 , LOW);
		digitalWrite(19 , LOW);
		digitalWrite(20 , LOW);
	}
	else if (ch == '@'){
		digitalWrite(15 , HIGH);
		digitalWrite(16 , HIGH);
		digitalWrite(17 , HIGH);
		digitalWrite(18 , HIGH);
		digitalWrite(19 , HIGH);
		digitalWrite(20 , HIGH);
		digitalWrite(13 , HIGH);
	}
	return ;
}

int main(void)
{
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(15, OUTPUT);
	pinMode(16, OUTPUT);
	pinMode(17, OUTPUT);
	pinMode(18, OUTPUT);
	pinMode(19, OUTPUT);
	pinMode(20, OUTPUT);
	pinMode(13, OUTPUT);
	//pinMode(8,INPUT);
	DDRC=0b00100110;
	CLKPR=(1<<CLKPCE);
	CLKPR=0b00000000;
	ADCSRA=0b10000111; // enable + prescaler
	ADMUX=0b11000000; // ref volt + channel
	ADCSRA |= (1<<ADEN);
	unsigned int BaudR = 9600;
	unsigned int ubrr = (F_CPU / (BaudR*16UL))-1;
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	UCSR0B |= (1<<TXEN0);
	while(1)
	{
		print();
		int currentDistance = readDistance();
		displayCharacter1('@');
		displayCharacter2('@');
		displayCharacter1((currentDistance/10)%10+'0');
		displayCharacter2(currentDistance%10+'0');
		_delay_ms(500);
	}
	
	
}




