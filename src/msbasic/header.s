		.segment "HEADER"
        jmp     COLD_START
.ifdef KBD
        jmp     LE68C
        .byte   $00,$13,$56
.endif
