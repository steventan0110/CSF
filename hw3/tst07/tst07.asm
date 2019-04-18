;--------------------------------------------------------------------;
;--------------------------------------------------------------------;
	ORG	0x00

	CLR		; Initialize accumulator
	CLC		; Initialize carry
	EXT	start	; Jump over reserved memory
	JMP	start
retv:	DAT	0xFF	; Reserved for subroutine return value
tmp0:	DAT	0x00	; Reserved for temporary variables
tmp1:	DAT	0x00
tmp2:	DAT	0x00
tmp3:	DAT	0x00
tmp4:	DAT	0x00
tmp5:	DAT	0x00
tmp6:	DAT	0x00
tmp7:	DAT	0x00
tmp8:	DAT	0x00
tmp9:	DAT	0x00
stkp:	DAT	0x00	; Reserved for stack pointer
			; stkp points to next available slot

	ORG	0x10
start:	; Initialize stack pointer
	SET		; Set accumulator to 0xFF
	STA	stkp	; Store 0xFF to stack pointer
	; Place argument (12) on stack
	CLR		; Load 13 into accumulator
	ADL	7
	ADL	6
	STI	stkp	; Save to stack
	; Decrement stack pointer
	LDA	stkp	; Load stack pointer
	ADL	-1	; Decrement
	STA	stkp	; Save stack pointer
	; Jump to subroutine fib
	CLR
	EXT	fib
	ADL	fib
	JAL
	; Restore stack pointer
	LDA	stkp	; Load stack pointer
	ADL	+1	; Increment
	STA	stkp	; Save stack pointer
	; Done
	HLT

fib:	; Save return address on stack
	STI	stkp	; Save to stack
	; Decrement stack pointer
	LDA	stkp	; Load stack pointer
	ADL	-1	; Decrement
	STA	stkp	; Save stack pointer

	; Compute argument address
	LDA	stkp	; Load stack pointer
	ADL	+2	; Adjust for argument address
	STA	tmp0	; Save address for LDI

	; Check if argument is 0
	LDI	tmp0	; Get argument
	TST		; Convert to 0 (zero) or +1 (not zero)
	NEG		; Convert to 0 (zero) or -1 (not zero)
	COM		; Convert to 0xFF (zero) or 0x00 (not zero)
	EXT	fib1	; Skip if argument not zero
	JMZ	fib1
	CLR		; Load 0
	STA	retv	; Save as return value
	EXT	fib3	; Skip to return code
	JMP	fib3

fib1:	; Check if argument is 1
	LDI	tmp0	; Get argument
	ADL	-1	; Convert to 0 (one) or other (not one)
	TST		; Convert to 0 (one) or +1 (not one)
	NEG		; Convert to 0 (one) or -1 (not one)
	COM		; Convert to 0xFF (one) or 0x00 (not one)
	EXT	fib2	; Skip if argument not one
	JMZ	fib2
	SET		; Load +1 (-1 negated)
	NEG
	STA	retv	; Save as return value
	EXT	fib3	; Skip to return code
	JMP	fib3

fib2:	; Place argument-1 on stack
	LDI	tmp0	; Get argument
	ADL	-1	; Subtract 1
	STI	stkp	; Save to stack
	; Decrement stack pointer
	LDA	stkp	; Load stack pointer
	ADL	-1	; Decrement
	STA	stkp	; Save stack pointer
	; Recursively call subroutine fib
	CLR
	EXT	fib
	ADL	fib
	JAL
	; Restore stack pointer
	LDA	stkp	; Load stack pointer
	ADL	+1	; Increment
	STA	stkp	; Save stack pointer

	; Save return value on stack
	LDA	retv	; Get return value
	STI	stkp	; Save to stack
	; Decrement stack pointer
	LDA	stkp	; Load stack pointer
	ADL	-1	; Decrement
	STA	stkp	; Save stack pointer

	; Compute argument address
	LDA	stkp	; Load stack pointer
	ADL	+3	; Adjust for argument address
	STA	tmp0	; Save address for LDI
	; Place argument-2 on stack
	LDI	tmp0	; Get argument
	ADL	-2	; Subtract 2
	STI	stkp	; Save to stack
	; Decrement stack pointer
	LDA	stkp	; Load stack pointer
	ADL	-1	; Decrement
	STA	stkp	; Save stack pointer
	; Recursively call subroutine fib
	CLR
	EXT	fib
	ADL	fib
	JAL
	; Restore stack pointer
	LDA	stkp	; Load stack pointer
	ADL	+1	; Increment
	STA	stkp	; Save stack pointer

	; Restore stack pointer
	LDA	stkp	; Load stack pointer
	ADL	+1	; Increment
	STA	stkp	; Save stack pointer
	; Add previous and current return value
	LDI	stkp
	ADD	retv
	STA	retv

fib3:	; Restore stack pointer
	LDA	stkp	; Load stack pointer
	ADL	+1	; Increment
	STA	stkp	; Save stack pointer
	; Get return address
	LDI	stkp
	; Return
	JAL
