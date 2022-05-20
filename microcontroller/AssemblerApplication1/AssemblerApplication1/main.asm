;
; AssemblerApplication1.asm
;
; Created: 5/18/2022 3:33:29 PM
; Author : USER
;


; Replace with your application code


setup:
	ldi r16, HIGH(RAMEND)
	out SPH, r16
	ldi r16, LOW(RAMEND)
	out SPL, r16
	ldi r16, 0b00000000
	out DDRD, r16
	ldi r16, 0b11111111
	out PORTD , r16 ;button input setup
	ldi r16, 0b11111111
	out DDRB, r16 ;7-segment output setup

mainLoop:
;r17 is used to store button input
	;call clearLED
	in r17, PIND
	cpi r17, 0b00000001 ;play C
		breq play_C
	cpi r17, 0b00000010 ;play D
		breq play_D
	cpi r17, 0b00000100 ;play E
		breq play_E
	cpi r17, 0b00001000 ;play F
		breq play_F
	cpi r17, 0b00010000 ;play G
		breq play_G
	cpi r17, 0b00100000 ;play A
		breq play_A
	cpi r17, 0b01000000 ;play B
		breq play_B

    rjmp mainLoop

endOfLoop:
	rjmp mainLoop

play_C:
	call clearLED
	ldi r19, 0b01000110
	call showLED
	rjmp endOfLoop

play_D:
	call clearLED
	ldi r19, 0b01000000
	call showLED
	rjmp endOfLoop

play_E:
	call clearLED
	ldi r19, 0b00000110
	call showLED
	rjmp endOfLoop

play_F:
	call clearLED
	ldi r19, 0b00001110
	call showLED
	rjmp endOfLoop

play_G:
	call clearLED
	ldi r19, 0b01000010
	call showLED
	rjmp endOfLoop

play_A:
	call clearLED
	ldi r19, 0b00001000
	call showLED
	rjmp endOfLoop

play_B:
	call clearLED
	ldi r19, 0b00000000
	call showLED
	rjmp endOfLoop

showLED:
; r19 is used to store 7-segment pattern
	out PORTB, r19
	ret

clearLED:
	ldi r19, 0b11111111
	call showLED
	ret


playSpeaker:
; r18 is used to store the delay time

delay:
	LDI R20, 12
L2: LDI R21, 12
L3: LDI R22, 2
L4: DEC R22
BRNE L4
DEC R21
BRNE L3
DEC R20
BRNE L2
RET

