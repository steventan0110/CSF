;--------------------------------------------------------------------;
; This program checks for the proper operation of the jumps and      ;
; conditional test instructions.                                     ;
;--------------------------------------------------------------------;
	ORG	0x00

	SET		; Initialize accumulator

	EXT	tgt01	; Test jump instruction
	JMP	tgt01
	HLT		; Not needed if JMP works
	HLT		; Fill
	HLT		; Fill
	HLT		; Fill
	HLT		; Fill
	HLT		; Fill
	HLT		; Fill
	HLT		; Fill
	HLT		; Fill
	HLT		; Fill
	HLT		; Fill
	HLT		; Fill
	HLT		; Fill
tgt01:	CLR		; Successful JMP
	EXT	res01
	STA	res01

	CLR		; Test conditional jump taken
	EXT	tgt02
	JMZ	tgt02
	HLT		; Not needed if JMZ works
tgt02:	CLR		; Successful JMZ taken
	EXT	res02
	STA	res02

	SET		; Test conditional jump not taken
	EXT	tgt03
	JMZ	tgt03
	CLR		; Successful JMZ not taken
	EXT	res03
	STA	res03

	EXT	argFF	; Test test instruction with 0xFF
	LDA	argFF
	TST		; ACC should now be 0x01
	NEG		; ACC should now be 0xFF
	COM		; ACC should now be 0x00
	EXT	tgt04
	JMZ	tgt04
	HLT		; Not needed if TST works
tgt04:	CLR		; Successful TST with 0xFF
	EXT	res04
	STA	res04

	CLR		; Test test instruction with 0x00
	TST		; ACC should now be 0x00
	EXT	tgt05
	JMZ	tgt05
	HLT		; Not needed if TST works
tgt05:	CLR		; Successful TST with 0xFF
	EXT	res05
	STA	res05

	EXT	arg40	; Test addition with positive overflow
	LDA	arg40
	EXT	arg40
	ADD	arg40
	TVA		; ACC should now be 0x01 (C=0, N=1)
	NEG		; ACC should now be 0xFF
	COM		; ACC should now be 0x00
	EXT	tgt06
	JMZ	tgt06
	HLT		; Not needed if TST works
tgt06:	CLR		; Successful overflow test
	EXT	res06
	STA	res06
	

	EXT	arg80	; Test addition with negative overflow
	LDA	arg80
	EXT	arg80
	ADD	arg80
	TVA		; ACC should now be 0x01 (C=1, N=0)
	NEG		; ACC should now be 0xFF
	COM		; ACC should now be 0x00
	EXT	tgt07
	JMZ	tgt07
	HLT		; Not needed if TST works
tgt07:	CLR		; Successful overflow test
	EXT	res07
	STA	res07
	
	EXT	argC0	; Test addition with no negative overflow
	LDA	argC0
	EXT	argC0
	ADD	argC0
	TVA		; ACC should now be 0x00 (C=1, N=1)
	EXT	tgt08
	JMZ	tgt08
	HLT		; Not needed if TST works
tgt08:	CLR		; Successful overflow test
	EXT	res08
	STA	res08

	HLT

tgt03:	HLT		; Not needed if JMZ works

	; Arguments for tests are stored here
arg40:	DAT	0x40
arg80:	DAT	0x80
argC0:	DAT	0xC0
argFF:	DAT	0xFF

	; Results of tests are stored here
res01:	DAT	0xFF
res02:	DAT	0xFF
res03:	DAT	0xFF
res04:	DAT	0xFF
res05:	DAT	0xFF
res06:	DAT	0xFF
res07:	DAT	0xFF
res08:	DAT	0xFF
