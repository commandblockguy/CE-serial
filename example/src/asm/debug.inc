debugAbort:
	call	debugNewLine
	call	debugStr
	db	'Abort called at ',0
	ld	b,5
	jr	.skip
.string:
	call	debugStr
	db	'<-',0
.skip:
	pop	hl
	call	debugHexUHL
	djnz	.string
	jr	$

debugHexBlockBC:
	ex	(sp),hl
	push	de
	push	bc
	push	af
	ld	de,(hl)
	inc	hl
	inc	hl
	inc	hl
.next:
	call	debugHex_DE_
	inc	de
	dec	bc
	ld	a,c
	or	a,b
	jr	nz,.next
	pop	af
	pop	bc
	pop	de
	ex	(sp),hl
	ret
debugHexBlockHL:
	ex	de,hl
	ex	(sp),hl
	push	de
	push	bc
	ld	b,(hl)
	inc	hl
.next:
	call	debugHex_DE_
	inc	de
	djnz	.next
	pop	bc
	pop	de
	ex	(sp),hl
	ex	de,hl
	ret
debugHexBlock:
	ex	(sp),hl
	push	de
	push	bc
	ld	de,(hl)
	inc	hl
	inc	hl
	inc	hl
	ld	b,(hl)
	inc	hl
.next:
	call	debugHex_DE_
	inc	de
	djnz	.next
	pop	bc
	pop	de
	ex	(sp),hl
	ret
debugHexBCU:
	push	af
	dec	sp
	push	bc
	jr	debugUpper
debugHexDEU:
	push	af
	dec	sp
	push	de
	jr	debugUpper
debugHexHLU:
	push	af
	dec	sp
	push	hl
debugUpper:
	inc	sp
	pop	af
	jr	debugDraw
debugHexB:
	push	af
	ld	a,b
	jr	debugDraw
debugHexD:
	push	af
	ld	a,d
	jr	debugDraw
debugHexH:
	push	af
	ld	a,h
	jr	debugDraw
debugHexUBC:
	call	debugHexBCU
debugHexBC:
	call	debugHexB
debugHexC:
	push	af
	ld	a,c
	jr	debugDraw
debugHexUDE:
	call	debugHexDEU
debugHexDE:
	call	debugHexD
debugHexE:
	push	af
	ld	a,e
	jr	debugDraw
debugHexUHL:
	call	debugHexHLU
debugHexHL:
	call	debugHexH
debugHexL:
	push	af
	ld	a,l
	jr	debugDraw
debugHex_BC_:
	push	af
	ld	a,(bc)
	jr	debugDraw
debugHex_DE_:
	push	af
	ld	a,(de)
	jr	debugDraw
debugHex_HL_:
	push	af
	ld	a,(hl)
	jr	debugDraw
debugHexA:
	push	af
debugDraw:
	push	iy
	ld	iy,flags
	push	af
	rrca
	rrca
	rrca
	rrca
	call	.draw
	pop	af
	call	.draw
	pop	iy
	pop	af
	ret
.draw:
	or	a,$F0
	daa
	add	a,$A0
	adc	a,$40
	jp	_PutC

debugDecHL:
	push	af
	push	de
	push	hl
	push	iy
	ld	iy,flags
	call	_DispHL_s
	pop	iy
	pop	hl
	pop	de
	pop	af
	ret
debugDecUHL:
	push	af
	push	de
	push	hl
	push	iy
	ld	iy,flags
	call	_DispHL
	pop	iy
	pop	hl
	pop	de
	pop	af
	ret

debugCharA:
	push	de
	push	bc
	push	af
	push	hl
	push	iy
	ld	iy,flags
	call	_PutC
	pop	iy
	pop	hl
	pop	af
	pop	bc
	pop	de
	ret

debugChar:
	ex	(sp), hl
	push	af
	push	iy
	ld	iy,flags
	ld	a,(hl)
	inc	hl
	call	_PutC
	pop	iy
	pop	af
	ex	(sp), hl
	ret

debugStr:
	ex	(sp),hl
	push	bc
	push	af
	push	de
	push	iy
	ld	iy,flags
	push	ix
	call	_PutS
	pop	ix
	pop	iy
	pop	de
	pop	af
	pop	bc
	ex	(sp),hl
	ret

debugNewLine:
	push	hl
	push	af
	push	de
	push	bc
	push	iy
	push	ix
	ld	iy,flags
	call	_NewLine
	pop	ix
	pop	iy
	pop	bc
	pop	de
	pop	af
	pop	hl
	ret
