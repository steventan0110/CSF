;--------------------------------------------------------------------;
; This program checks for the proper handling of the carry when      ;
; performing arithmetic.                                             ;
;--------------------------------------------------------------------;
	ORG	0x00

	; Tests 1 and 2
	; Check that the carry can set/cleared and be transferred to
	; the accumulator
	SET
	CLC
	TCA
	EXT	res01	; Should be 0
	STA	res01
	SET
	SEC
	TCA
	EXT	res02	; Should be 1
	STA	res02

	; Tests 3 and 4
	; Check that the carry is set/cleared with ADD
	CLR
	EXT	argFF
	ADD	argFF
	TCA
	EXT	res03	; Should be 0
	STA	res03
	SET
	EXT	arg01
	ADD	arg01
	TCA
	EXT	res04	; Should be 1
	STA	res04

	; Tests 5 and 6
	; Check that the carry is set/cleared with SUB
	CLR
	EXT	arg01
	SUB	arg01
	TCA
	EXT	res05	; Should be 0
	STA	res05
	SET
	EXT	argFF
	SUB	argFF
	TCA
	EXT	res06	; Should be 1
	STA	res06

	; Tests 7 and 8
	; Check that the carry is set/cleared with ADC
	CLC
	CLR
	EXT	argFF
	ADD	argFF
	TCA
	EXT	res07	; Should be 0
	STA	res07
	CLC
	SET
	EXT	arg01
	ADD	arg01
	TCA
	EXT	res08	; Should be 1
	STA	res08

	; Tests 9 and 10
	; Check that the carry is set/cleared with SUB
	SEC
	CLR
	EXT	arg01
	SUB	arg01
	TCA
	EXT	res09	; Should be 0
	STA	res09
	SEC
	SET
	EXT	argFF
	SUB	argFF
	TCA
	EXT	res10	; Should be 1
	STA	res10

	; Tests 11 and 12
	; Check that the carry is set/cleared with ADL
	CLR
	ADL	0x0F
	TCA
	EXT	res11	; Should be 0
	STA	res11
	SET
	ADL	0x01
	TCA
	EXT	res12	; Should be 1
	STA	res12

	; Test a two byte addition with a carry
	EXT	arg83
	LDA	arg83
	EXT	arg80
	ADD	arg80
	EXT	res13l	; Should be 3
	STA	res13l
	EXT	arg81
	LDA	arg81
	EXT	arg80
	ADC	arg80
	EXT	res13h	; Should be 2
	STA	res13h
	TCA
	EXT	res13c	; Should be 1
	STA	res13c

	; Test a two byte subtraction with a borrow
	EXT	arg00
	LDA	arg00
	EXT	argFD
	SUB	argFD
	EXT	res14l	; Should be 3
	STA	res14l
	EXT	arg83
	LDA	arg83
	EXT	arg80
	SBB	arg80
	EXT	res14h	; Should be 2
	STA	res14h
	TCA
	EXT	res14c	; Should be 1
	STA	res14c

	; End of tests
	HLT

	; Arguments for tests are stored here
arg00:	DAT	0x00
arg01:	DAT	0x01
arg80:	DAT	0x80
arg81:	DAT	0x81
arg83:	DAT	0x83
argFD:	DAT	0xFD
argFF:	DAT	0xFF

	; Results of tests are stored here
res01:	DAT	0xF0	; Result of test 1
res02:	DAT	0xF0	; Result of test 2
res03:	DAT	0xF0	; Result of test 3
res04:	DAT	0xF0	; Result of test 4
res05:	DAT	0xF0	; Result of test 5
res06:	DAT	0xF0	; Result of test 6
res07:	DAT	0xF0	; Result of test 7
res08:	DAT	0xF0	; Result of test 8
res09:	DAT	0xF0	; Result of test 9
res10:	DAT	0xF0	; Result of test 10
res11:	DAT	0xF0	; Result of test 11
res12:	DAT	0xF0	; Result of test 12
res13l:	DAT	0xF0	; Result of test 13 (three bytes)
res13h:	DAT	0xF0
res13c:	DAT	0xF0
res14l:	DAT	0xF0	; Result of test 14 (three bytes)
res14h:	DAT	0xF0
res14c:	DAT	0xF0
