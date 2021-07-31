.segment "CODE"

; 21x12 display

reset           =       $8000   ; reset
btout           =       $8003   ; btout
chout           =       $8006   ; chout
chin            =       $8009   ; chin
delay           =       $800C   ; delay

ESC             =       $1B     ; escape
LTRA            =       $61     ; letter a
CNT             =       $1A     ; 26 letters

                lda     #ESC    ; Clear the screen
                jsr     chout    
begin:
                lda     #LTRA   ; ASCII for A
                ldx     #CNT    ; a through z
loop:
                jsr     chout
                clc
                adc     #$01
                dex
                bne     loop
                jsr     chin
                cmp     #ESC
                bne     begin
                jmp     reset
