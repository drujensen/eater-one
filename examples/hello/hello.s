.segment "CODE"

; 21x12 display

reset           =       $8000   ; reset
btout           =       $8003   ; btout
chout           =       $8006   ; chout
chin            =       $8009   ; chin
delay           =       $800C   ; delay

ESC             =       $1B     ; escape

begin:
                lda     #ESC    ; Clear the screen
                jsr     chout    
                ldx     #$00    ; counter
loop:
                lda     message,x
                beq     end
                jsr     chout
                inx
                jmp     loop
end:
                jmp     reset

.segment "DATA"

message:
                .asciiz "Hello, World!"
