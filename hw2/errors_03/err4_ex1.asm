; This example should produce an error with return value 4
;
; Note that the binary produced by the assembler must be
; post-processed to remove the last byte (e.g. using dd).
	ORG	0
	CLR
	EXT	15
	JMP	15
