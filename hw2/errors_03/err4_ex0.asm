; This example should not produce an error
	ORG	0
	CLR
	STA	0
	EXT	15
	JMP	15
	ORG	255
	NOP		; PC should wrap around to zero
