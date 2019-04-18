;--------------------------------------------------------------------;
; This program checks for the proper operation of the shift and      ;
; rotate instructions.                                               ;
;--------------------------------------------------------------------;
	ORG	0x00

	SET
	EXT	res01	; Should be 0xFF
	STA	res01
	LSL
	EXT	res02	; Should be 0xFE
	STA	res02
	LSL
	EXT	res03	; Should be 0xFC
	STA	res03
	LSL
	EXT	res04	; Should be 0xF8
	STA	res04
	LSL
	EXT	res05	; Should be 0xF0
	STA	res05
	LSL
	EXT	res06	; Should be 0xE0
	STA	res06
	LSL
	EXT	res07	; Should be 0xC0
	STA	res07
	LSL
	EXT	res08	; Should be 0x80
	STA	res08
	ASR
	EXT	res09	; Should be 0xC0
	STA	res09
	ASR
	EXT	res10	; Should be 0xE0
	STA	res10
	ASR
	EXT	res11	; Should be 0xF0
	STA	res11
	ASR
	EXT	res12	; Should be 0xF8
	STA	res12
	ASR
	EXT	res13	; Should be 0xFC
	STA	res13
	ASR
	EXT	res14	; Should be 0xFE
	STA	res14
	ASR
	EXT	res15	; Should be 0xFF
	STA	res15
	LSR
	EXT	res16	; Should be 0x7F
	STA	res16
	LSR
	EXT	res17	; Should be 0x3F
	STA	res17
	LSR
	EXT	res18	; Should be 0x1F
	STA	res18
	LSR
	EXT	res19	; Should be 0x0F
	STA	res19
	LSR
	EXT	res20	; Should be 0x07
	STA	res20
	LSR
	EXT	res21	; Should be 0x03
	STA	res21
	LSR
	EXT	res22	; Should be 0x01
	STA	res22
	RTR
	EXT	res23	; Should be 0x80
	STA	res23
	RTR
	EXT	res24	; Should be 0x40
	STA	res24
	RTR
	EXT	res25	; Should be 0x20
	STA	res25
	RTR
	EXT	res26	; Should be 0x10
	STA	res26
	RTR
	EXT	res27	; Should be 0x08
	STA	res27
	RTR
	EXT	res28	; Should be 0x04
	STA	res28
	RTR
	EXT	res29	; Should be 0x02
	STA	res29
	RTR
	EXT	res30	; Should be 0x01
	STA	res30
	RTR
	EXT	res31	; Should be 0x80
	STA	res31
	RTL
	EXT	res32	; Should be 0x01
	STA	res32
	RTL
	EXT	res33	; Should be 0x02
	STA	res33
	RTL
	EXT	res34	; Should be 0x04
	STA	res34
	RTL
	EXT	res35	; Should be 0x08
	STA	res35
	RTL
	EXT	res36	; Should be 0x10
	STA	res36
	RTL
	EXT	res37	; Should be 0x20
	STA	res37
	RTL
	EXT	res38	; Should be 0x40
	STA	res38
	RTL
	EXT	res39	; Should be 0x80
	STA	res39
	ADL	-1
	EXT	res40	; Should be 0x7F
	STA	res40
	ASR
	EXT	res41	; Should be 0x3F
	STA	res41
	ASR
	EXT	res42	; Should be 0x1F
	STA	res42
	ASR
	EXT	res43	; Should be 0x0F
	STA	res43
	ASR
	EXT	res44	; Should be 0x07
	STA	res44
	ASR
	EXT	res45	; Should be 0x03
	STA	res45
	ASR
	EXT	res46	; Should be 0x01
	STA	res46
	ASR
	EXT	res47	; Should be 0x00
	STA	res47

	HLT

res01:	DAT	0xAA
res02:	DAT	0xAA
res03:	DAT	0xAA
res04:	DAT	0xAA
res05:	DAT	0xAA
res06:	DAT	0xAA
res07:	DAT	0xAA
res08:	DAT	0xAA
res09:	DAT	0xAA
res10:	DAT	0xAA
res11:	DAT	0xAA
res12:	DAT	0xAA
res13:	DAT	0xAA
res14:	DAT	0xAA
res15:	DAT	0xAA
res16:	DAT	0xAA
res17:	DAT	0xAA
res18:	DAT	0xAA
res19:	DAT	0xAA
res20:	DAT	0xAA
res21:	DAT	0xAA
res22:	DAT	0xAA
res23:	DAT	0xAA
res24:	DAT	0xAA
res25:	DAT	0xAA
res26:	DAT	0xAA
res27:	DAT	0xAA
res28:	DAT	0xAA
res29:	DAT	0xAA
res30:	DAT	0xAA
res31:	DAT	0xAA
res32:	DAT	0xAA
res33:	DAT	0xAA
res34:	DAT	0xAA
res35:	DAT	0xAA
res36:	DAT	0xAA
res37:	DAT	0xAA
res38:	DAT	0xAA
res39:	DAT	0xAA
res40:	DAT	0xAA
res41:	DAT	0xAA
res42:	DAT	0xAA
res43:	DAT	0xAA
res44:	DAT	0xAA
res45:	DAT	0xAA
res46:	DAT	0xAA
res47:	DAT	0xAA
