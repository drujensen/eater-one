.segment "CODE"
ISCNTC:
        lda     $7C0D           ; keyboard status
        and     #%00000010      ; check keyboard bit
        bne     L0ECC           ; branch if key pressed
        rts                     ; return
L0ECC:
        lda     $7C01           ; get key data
        cmp     #$83            ; is it Ctrl-C ?
;!!! *used*to* run into "STOP"
