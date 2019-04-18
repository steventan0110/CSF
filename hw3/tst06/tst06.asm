;--------------------------------------------------------------------;
; This program checks for the proper operation of miscellanous       ;
; instructions, such as logical and indirect.                        ;
;--------------------------------------------------------------------;
	ORG	0x00

	CLR		; Initialize accumulator
	EXT	start	; Jump to start
	JMP	start

	ORG	0x10
start:	EXT	arg3C	; Test AND
	LDA	arg3C
	EXT	arg5A
	AND	arg5A
	EXT	res01	; Should be 0x18
	STA	res01

	EXT	arg3C	; Test IOR (OR)
	LDA	arg3C
	EXT	arg5A
	IOR	arg5A
	EXT	res02	; Should be 0x7E
	STA	res02

	EXT	arg3C	; Test XOR
	LDA	arg3C
	EXT	arg5A
	XOR	arg5A
	EXT	res03	; Should be 0x66
	STA	res03

	EXT	ind01	; Test LDI
	LDI	ind01
	EXT	res04	; Should be 0x3C
	STA	res04

	EXT	arg5A	; Test STI
	LDA	arg5A
	EXT	ind02	; Should be 0x5A
	STI	ind02

	HLT

	; Arguments for tests are stored here
arg3C:	DAT	0x3C	; 0011 1100
arg5A:	DAT	0x5A	; 0101 1010
ind01:	DAT	arg3C
ind02:	DAT	res05

	; Results of tests are stored here
res01:	DAT	0xFF
res02:	DAT	0xFF
res03:	DAT	0xFF
res04:	DAT	0xFF
res05:	DAT	0xFF
