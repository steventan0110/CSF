;--------------------------------------------------------------------;
; This program checks for the proper operation of the subroutine     ;
; jump-and-link instruction.                                         ;
;--------------------------------------------------------------------;
	ORG	0x00

	CLR		; Load subroutine address into accumulator
	EXT	return
	ADL	return

	JAL		; Jump to subroutine

	ADL	1	; Detect wrong return address
	ADL	1
	ADL	1
	ADL	1
	ADL	1
	ADL	1
	ADL	1
	ADL	1
	ADL	1

	EXT	acsave	; Save accumulator, should be 0x1C
	STA	acsave
	HLT

return:	EXT	pcsave	; Save PC, should be 0x04
	STA	pcsave
	JAL
	HLT		; Not needed if JAL works

pcsave:	DAT	0x55	; Place to save PC
acsave: DAT	0xFF	; Place to save accumulator
