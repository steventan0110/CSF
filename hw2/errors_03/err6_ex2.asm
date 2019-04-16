; This example should produce an error with return value 6
;
; Note that the binary produced by the assembler must be
; post-processed to remove the last byte (e.g. using dd).
	ORG	0
	CLR
	STI	arg
	HLT
arg:	DAT	255
