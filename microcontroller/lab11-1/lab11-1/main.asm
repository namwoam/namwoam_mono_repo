	.EQU SUM = 0x300
	LDI R16, 0x25
	LDI R17, 0x34
	LDI R18, 0x31
	ADD R16, R17
	ADD R16, R18
	LDI R17, 0x74
	ADD R16, R17
	LDI R20, 0
	ADD R16, R20
	LDI R21, 0xFF
	OUT DDRD, R21
L2: INC R20
	OUT PORTD, R20
	STS SUM, R20
	RJMP L2
