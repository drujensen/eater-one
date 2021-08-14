;
; File generated by cc65 v 2.18 - N/A
;
	.fopt		compiler,"cc65 v 2.18 - N/A"
	.setcpu		"6502"
	.smart		on
	.autoimport	on
	.case		on
	.debuginfo	off
	.importzp	sp, sreg, regsave, regbank
	.importzp	tmp1, tmp2, tmp3, tmp4, ptr1, ptr2, ptr3, ptr4
	.macpack	longbranch
	.forceimport	__STARTUP__
	.import		_printf
	.export		_main

.segment	"RODATA"

L000B:
	.byte	$25,$64,$0A,$00

; ---------------------------------------------------------------
; int __near__ fib (int)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_fib: near

.segment	"CODE"

	jsr     pushax
	ldy     #$01
	jsr     ldaxysp
	cmp     #$02
	txa
	sbc     #$00
	bvc     L0004
	eor     #$80
L0004:	asl     a
	lda     #$00
	ldx     #$00
	rol     a
	jeq     L0002
	ldx     #$00
	lda     #$01
	jmp     L0001
L0002:	ldy     #$01
	jsr     ldaxysp
	jsr     decax1
	jsr     _fib
	jsr     pushax
	ldy     #$03
	jsr     ldaxysp
	jsr     decax2
	jsr     _fib
	jsr     tosaddax
	jmp     L0001
L0001:	jsr     incsp2
	rts

.endproc

; ---------------------------------------------------------------
; int __near__ main (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_main: near

.segment	"CODE"

	lda     #<(L000B)
	ldx     #>(L000B)
	jsr     pushax
	ldx     #$00
	lda     #$2E
	jsr     _fib
	jsr     pushax
	ldy     #$04
	jsr     _printf
	ldx     #$00
	lda     #$00
	jmp     L0009
L0009:	rts

.endproc
