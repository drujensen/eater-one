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

L0003:
	.byte	$0A,$48,$45,$4C,$4C,$4F,$2C,$20,$57,$4F,$52,$4C,$44,$21,$0A,$00

; ---------------------------------------------------------------
; int __near__ main (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_main: near

.segment	"CODE"

	lda     #<(L0003)
	ldx     #>(L0003)
	jsr     pushax
	ldy     #$02
	jsr     _printf
	ldx     #$00
	txa
	rts

.endproc

