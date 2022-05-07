/*
* test.c
*
* Created: 3/23/2022 3:05:39 PM
* Author : USER
*/


#define F_CPU 8000000UL
#define INPUT 0
#define OUTPUT 1
#define HIGH 1
#define LOW 0
#define SPECIALPORT 16

#include <avr/io.h>
#include <avr/delay.h>

char currentCharacter = '@';

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

/*

void displayNumber(int n){
if (n == 0){

}
else if (n == 1){

}
else if (n == 2){

}
else if (n == 3){

}
else if (n==4){

}
else if (n==5){

}
else if (n==6){

}
else if (n==7){

}
else if (n==8){

}
else if (n==9){

}
else if (n==0){

}
else if (n == -1){

}
return ;
}
*/

void displayCharacter(char ch){
	if (ch == 'A'){
		digitalWrite(8 , LOW);
		digitalWrite(9 , LOW);
		digitalWrite(10 , LOW);
		digitalWrite(12 , LOW);
		digitalWrite(13 , LOW);
		digitalWrite(SPECIALPORT , LOW);
	}
	else if (ch == 'B'){
		digitalWrite(8 , LOW);
		digitalWrite(9 , LOW);
		digitalWrite(10 , LOW);
		digitalWrite(11 , LOW);
		digitalWrite(12 , LOW);
		digitalWrite(13 , LOW);
		digitalWrite(SPECIALPORT , LOW);
		
	}
	else if (ch == 'C'){
		digitalWrite(8 , LOW);
		digitalWrite(11 , LOW);
		digitalWrite(12 , LOW);
		digitalWrite(13 , LOW);
	}
	else if (ch == 'D'){
		digitalWrite(8 , LOW);
		digitalWrite(9 , LOW);
		digitalWrite(10 , LOW);
		digitalWrite(11 , LOW);
		digitalWrite(12 , LOW);
		digitalWrite(13 , LOW);
	}
	else if (ch == 'E'){
		digitalWrite(8 , LOW);
		digitalWrite(11 , LOW);
		digitalWrite(12 , LOW);
		digitalWrite(13 , LOW);
		digitalWrite(SPECIALPORT , LOW);
	}
	else if (ch == 'F'){
		digitalWrite(8 , LOW);
		digitalWrite(12 , LOW);
		digitalWrite(13 , LOW);
		digitalWrite(SPECIALPORT , LOW);
	}
	else if (ch == '1'){
		digitalWrite(9 , LOW);
		digitalWrite(10 , LOW);
	}
	else if (ch == '2'){
		digitalWrite(8 , LOW);
		digitalWrite(9 , LOW);
		digitalWrite(11 , LOW);
		digitalWrite(12 , LOW);
		digitalWrite(SPECIALPORT , LOW);
	}
	else if (ch == '3'){
		digitalWrite(8 , LOW);
		digitalWrite(9 , LOW);
		digitalWrite(10 , LOW);
		digitalWrite(11 , LOW);
		digitalWrite(SPECIALPORT, LOW);
	}
	else if (ch == '4'){
		digitalWrite(9 , LOW);
		digitalWrite(10 , LOW);
		digitalWrite(13 , LOW);
		digitalWrite(SPECIALPORT , LOW);
	}
	else if (ch == '5'){
		digitalWrite(8 , LOW);
		digitalWrite(10 , LOW);
		digitalWrite(11 , LOW);
		digitalWrite(13 , LOW);
		digitalWrite(SPECIALPORT , LOW);
	}
	else if (ch == '6'){
		digitalWrite(8 , LOW);
		digitalWrite(10 , LOW);
		digitalWrite(11 , LOW);
		digitalWrite(12 , LOW);
		digitalWrite(13 , LOW);
		digitalWrite(SPECIALPORT , LOW);
	}
	else if (ch == '7'){
		digitalWrite(8 , LOW);
		digitalWrite(9 , LOW);
		digitalWrite(10 , LOW);
		digitalWrite(13 , LOW);
	}
	else if (ch == '8'){
		digitalWrite(8 , LOW);
		digitalWrite(9 , LOW);
		digitalWrite(10 , LOW);
		digitalWrite(11 , LOW);
		digitalWrite(12 , LOW);
		digitalWrite(13 , LOW);
		digitalWrite(SPECIALPORT , LOW);
	}
	else if (ch == '9'){
		digitalWrite(8 , LOW);
		digitalWrite(9 , LOW);
		digitalWrite(10 , LOW);
		digitalWrite(11 , LOW);
		digitalWrite(13 , LOW);
		digitalWrite(SPECIALPORT , LOW);
	}
	else if (ch == '0'){
		digitalWrite(8 , LOW);
		digitalWrite(9 , LOW);
		digitalWrite(10 , LOW);
		digitalWrite(11 , LOW);
		digitalWrite(12 , LOW);
		digitalWrite(13 , LOW);
	}
	else if (ch == '@'){
		digitalWrite(8 , HIGH);
		digitalWrite(9 , HIGH);
		digitalWrite(10 , HIGH);
		digitalWrite(11 , HIGH);
		digitalWrite(12 , HIGH);
		digitalWrite(13 , HIGH);
		digitalWrite(SPECIALPORT , HIGH);
	}
	return ;
}

void clear(){
	displayCharacter('@');
}

void display(){
	// PC0 PC1 PC2 PC3 PC4 PC5 PC6 output
	// shine -> low , dark -> high
	displayCharacter(currentCharacter);
}

void checkInput(){
	int result = -1;
	for (int i=0;i<4;i++){
		digitalWrite(i+4 , HIGH);
		for (int k=0;k<4;k++){
			if (digitalRead(k) == HIGH){
				result = (i+1)*10+(k+1);
			}
		}
		digitalWrite(i+4 , LOW);
	}
	if (result == -1){
		return ;
	}
	else {
		clear();
		if (result == 11){
			currentCharacter = '7';
		}
		else if (result == 12){
			currentCharacter = '8';
		}
		else if (result == 13){
			currentCharacter = '9';
		}
		else if (result == 14){
			currentCharacter = 'C';
		}
		else if (result == 21){
			currentCharacter = '4';
		}
		else if (result == 22){
			currentCharacter = '5';
		}
		else if (result == 23){
			currentCharacter = '6';
		}
		else if (result == 24){
			currentCharacter = 'D';
		}
		else if (result == 31){
			currentCharacter = '1';
		}
		else if (result == 32){
			currentCharacter = '2';
		}
		else if (result == 33){
			currentCharacter = '3';
		}
		else if (result == 34){
			currentCharacter = 'E';
		}
		else if (result == 41){
			currentCharacter = '0';
		}
		else if (result == 42){
			currentCharacter = 'A';
		}
		else if (result == 43){
			currentCharacter = 'B';
		}
		else if (result == 44){
			currentCharacter = 'F';
		}
		
	}
	
}

int main(void)
{
	pinMode(0 , INPUT);
	pinMode(1 , INPUT);
	pinMode(2 , INPUT);
	pinMode(3 , INPUT);
	pinMode(4 , OUTPUT);
	pinMode(5 , OUTPUT);
	pinMode(6 , OUTPUT);
	pinMode(7 , OUTPUT);
	pinMode(8 , OUTPUT);
	pinMode(9 , OUTPUT);
	pinMode(10 , OUTPUT);
	pinMode(11 , OUTPUT);
	pinMode(12 , OUTPUT);
	pinMode(13 , OUTPUT);
	pinMode(SPECIALPORT , OUTPUT);
	for (int i=8;i<=14;i++){
		digitalWrite(i , LOW);
	}
	digitalWrite(SPECIALPORT , LOW);
	/* Replace with your application code */
	//displayCharacter('A');
	
	while(1)
	{
		/*
		displayCharacter('0');
		_delay_ms(1000);
		clear();
		displayCharacter('1');
		_delay_ms(1000);
		clear();
		displayCharacter('2');
		_delay_ms(1000);
		clear();
		displayCharacter('3');
		_delay_ms(1000);
		clear();
		displayCharacter('4');
		_delay_ms(1000);
		clear();
		displayCharacter('5');
		_delay_ms(1000);
		clear();
		displayCharacter('6');
		_delay_ms(1000);
		clear();
		displayCharacter('7');
		_delay_ms(1000);
		clear();
		displayCharacter('8');
		_delay_ms(1000);
		clear();
		displayCharacter('9');
		_delay_ms(1000);
		clear();
		displayCharacter('A');
		_delay_ms(1000);
		clear();
		displayCharacter('B');
		_delay_ms(1000);
		clear();
		displayCharacter('C');
		_delay_ms(1000);
		clear();
		displayCharacter('D');
		_delay_ms(1000);
		clear();
		displayCharacter('E');
		_delay_ms(1000);
		clear();
		displayCharacter('F');
		_delay_ms(1000);
		clear();
		*/
		checkInput();
		display();

	}
	
}

