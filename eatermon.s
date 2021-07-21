;-------------------------------------------------------------------------
;
;  The WOZ Monitor for the Apple 1
;  Written by Steve Wozniak 1976
;  Modified to support Ben Eaters C6502 Breadboard
;-------------------------------------------------------------------------

.segment "OS"

;-------------------------------------------------------------------------
;  Memory declaration
;-------------------------------------------------------------------------

XAML            =       $24         ; Last "opened" location Low
XAMH            =       $25         ; Last "opened" location High
STL             =       $26         ; Store address Low
STH             =       $27         ; Store address High
L               =       $28         ; Hex value parsing Low
H               =       $29         ; Hex value parsing High
YSAV            =       $2A         ; Used to see if hex value is given
MODE            =       $2B         ; $00=XAM, $7F=STOR, $AE=BLOCK XAM

IN              =       $0200       ; Input buffer

DSP             =       $6000       ; Display Output Register B
DSPDR           =       $6002       ; Display Data Direction Register B
KBD             =       $6001       ; Keyboard Input Register A
KBDDR           =       $6003       ; Keyboard Data Direction Register A

PCR             =       $600C       ; Peripheral Control Register
IFR             =       $600D       ; Interrupt Flag Register
IER             =       $600E       ; Ineterrup Enable Register
E               =       %01000000   ; Display Enable Bit
RW              =       %00100000   ; Display RW Flag
RS              =       %00010000   ; Display Register Select

;-------------------------------------------------------------------------
;  Constants
;-------------------------------------------------------------------------

SPACE           =       $20         ; Space
BS              =       $7F         ; Back Space
CR              =       $0D         ; Carriage Return
ESC             =       $1B         ; ESC key
PROMPT          =       '>'         ; Prompt character

;-------------------------------------------------------------------------
;  Let's get started
;
;  Remark the RESET routine is only to be entered by asserting the RESET
;  line of the system. This ensures that the data direction registers
;  are selected.
;-------------------------------------------------------------------------
reset:
                ldx     #$FF        ; Set Stack pointer to FF
                txs

                cld                 ; Clear decimal arithmetic mode
                cli
                lda     #%11111111  ; Set all pins on port B to output
                sta     DSPDR
                lda     #%00000000  ; Set all pins on port A to input
                sta     KBDDR
                lda     #%00000001  ; Set positive active edge for CA1
                sta     PCR
                lda     #%10000010  ; enable CA1 interrupt
                sta     IER

; The following is specific initialization of the LCD Display and not found in the
; original WozMon source code.

                jsr     lcd_init
                lda     #%00101000  ; Set 4-bit mode; 2-line display; 5x8 font
                jsr     lcd_inst
                lda     #%00001111  ; Display on; cursor on; blink on
                jsr     lcd_inst
                lda     #%00000110  ; Increment and shift cursor; don't shift display
                jsr     lcd_inst
                lda     #%00000001  ; Clear display
                jsr     lcd_inst

; The program has been modified to use the IRQ instead of the 7tbh bit of the keybard.
; This allows support for 8bit ASCII codes from the keyboard.  We will display the
; prompt and loop forever.

                lda     #PROMPT
                jsr     lcd_echo

loop:
                jmp     loop


;-------------------------------------------------------------------------
; The GETLINE process
;-------------------------------------------------------------------------
; Called by the Interrupt Handler
nextchar:
                lda     KBD
                sta     IN,Y
                cmp     #BS
                beq     backspace
                cmp     #ESC
                beq     escape
                cmp     #CR
                beq     enter
                jsr     lcd_echo
                iny
                rts

backspace:
                lda     #%00000100  ; Change display to decrement mode
                jsr     lcd_inst
                lda     #SPACE      ; Clear the previous display
                jsr     lcd_echo
                lda     #%00000110  ; Change display back to increment mode
                jsr     lcd_inst
                lda     #$00        ; clear value from buffer
                sta     IN,Y
                dey                 ; Decrement the buffer pointer
                rts

escape:
                lda     #%00000001  ; Clear display
                jsr     lcd_inst
                lda     #PROMPT     ; Print promt character
                jsr     lcd_echo    ; Output it.
                ldy     #$00        ; Reset the buffer pointer
                rts

enter:
                jsr     lcd_scroll  ; Scroll to the next line

; Line received, now let's parse it

                ldy     #$ff
                lda     #$00
                tax

setstor:
                asl                 ; Leaves $7B if setting STOR mode

setmode:
                sta     MODE        ; Set mode flags

blskip:
                iny                 ; Advance text index

nextitem:
                lda     IN,Y        ; Get character
                cmp     #CR
                bne     notdone
                jsr     lcd_home    ; We're done if it's CR!
                rts

notdone:
                cmp     #'.'        ;
                bcc     blskip      ; Ignore everything below '.'!
                beq     setmode     ; Set BLOCK XAM mode ("." = $AE)
                cmp     #':'
                beq     setstor     ; Set STORE mode! $BA will become $7B
                cmp     #'R'
                beq     run         ; Run the program!  Forget the rest
                stx     L           ; Clear input value (X=0)
                stx     H
                sty     YSAV        ; Save Y for comparison

; Here we're trying to parse a new hex value

nexthex:
                lda     IN,Y        ; Get character for hex test
                eor     #$30        ; Map digits to 0-9.  Wozmon originally #$B0
                cmp     #9+1        ; Is it a decimal digit?
                bcc     dig         ; Yes!
                adc     #$88        ; Map letter "A" - "F" to $FA-$FF
                cmp     #$fa        ; Hex letter?
                bcc     nothex      ; No! Character not hex

dig:
                asl                 ; Hex digit to MSD of A
                asl
                asl
                asl

                ldx     #4          ; Shift count
hexshift:
                asl                 ; Hex digit left, MSB to carry
                rol     L           ; Rotate into LSD
                rol     H           ; Rotate into MSD
                dex                 ; Done 4 shifts?
                bne     hexshift    ; No, loop
                iny                 ; Advance text index
                bne     nexthex     ; Always taken

nothex:
                cpy     YSAV        ; Was at least 1 hex digit given?
                beq     escape      ; No! Ignore all, start from scratch

                bit     MODE        ; Test MODE byte
                bvc     notstor     ; B6=0 is STOR, 1 is XAM or BLOCK XAM

; STOR mode, save LSD of new hex byte

                lda     L           ; LSD's of hex data
                sta     (STL,X)     ; Store current 'store index'(X=0)
                inc     STL         ; Increment store index
                BNE     nextitem    ; No carry!
                inc     STH         ; Add carry to 'store index' high

tonextitem:
                jmp     nextitem    ; Get next command item.

;-------------------------------------------------------------------------
;  RUN user's program from last opened location
;-------------------------------------------------------------------------

run:
                jmp     (XAML)

;-------------------------------------------------------------------------
;  We're not in Store mode
;-------------------------------------------------------------------------

notstor:
                bmi     xamnext      ; B7 = 0 for XAM, 1 for BLOCK XAM

; We're in XAM mode now

                ldx     #2           ; Copy 2 bytes
setadr:
                lda     L-1,X        ; Copy hex data to
                sta     STL-1,X      ; 'store index'
                sta     XAML-1,X     ; and to 'XAM index'
                dex                  ; Next of 2 bytes
                bne     setadr       ; Loop unless X = 0

; Print address and data from this address, fall through next BNE.

nxtprnt:
                bne     prdata       ; NE means no address to print
                jsr     lcd_scroll   ; Print newline
                lda     XAMH         ; Output high-order byte of address
                jsr     prbyte
                lda     XAML         ; Output low-order byte of address
                jsr     prbyte
                lda     #':'         ; Print colon
                jsr     lcd_echo

prdata:
                lda     #SPACE        ; Print space
                jsr     lcd_echo
                lda     (XAML,X)     ; Get data from address (X=0)
                jsr     prbyte       ; Output it in hex format

xamnext:
                stx     MODE         ; 0 -> MODE (XAM mode).
                lda     XAML         ; See if there's more to print
                cmp     L
                lda     XAMH
                sbc     H
                bcs     tonextitem   ; Not less! No more data to output

                inc     XAML         ; Increment 'examine index'
                bne     mod8chk      ; No carry!
                inc     XAMH

mod8chk:
                lda     XAML         ; If address MOD 8 = 0 start new line
                and     #%00000111
                bpl     nxtprnt      ; Always taken.

;-------------------------------------------------------------------------
;  Subroutine to print a byte in A in hex form (destructive)
;-------------------------------------------------------------------------

prbyte:
                pha                  ; Save A for LSD
                lsr
                lsr
                lsr                  ; MSD to LSD position
                lsr
                jsr     prhex        ; Output hex digit
                pla

; Fall through to print hex routine

;-------------------------------------------------------------------------
;  Subroutine to print a hexadecimal digit
;-------------------------------------------------------------------------

prhex:
                and     #%00001111   ; Mast LSD for hex print
                ora     #'0'         ; Add "0"
                cmp     #'9'+1       ; Is it a decimal digit?
                bcc     lcd_echo     ; Yes! output it
                adc     #6           ; Add offset for letter A-F
                jsr     lcd_echo     ; Print it
                rts                  ;

;-------------------------------------------------------------------------
;  Subroutine to print a character to the terminal.  Modified to support
;  LCD Display.
;-------------------------------------------------------------------------
lcd_init:
                lda     #%00000010    ; Set 4-bit mode
                sta     DSP
                ora     #E            ; Set Enable bit
                sta     DSP
                eor     #E            ; Clear Enable bit
                sta     DSP
                jsr     lcd_wait      ; Wait for display
                rts

lcd_inst:
                pha                   ; Push A for LSD later
                lsr
                lsr                   ; MSD to LSD position
                lsr
                lsr                   ; Send high 4 bits
                sta     DSP
                ora     #E            ; Set Enable bit
                sta     DSP
                eor     #E            ; Clear Enable bit
                sta     DSP
                pla
                and     #%00001111    ; Mask LSD
                sta     DSP
                ora     #E            ; Set Enable bit
                sta     DSP
                eor     #E            ; Clear Enable bit
                sta     DSP
                jsr     lcd_wait      ; Wait for Display
                rts

lcd_echo:
                pha                   ; Push A for LSD later
                lsr
                lsr                   ; MSD to LSD position
                lsr
                lsr
                ora     #RS           ; Set Register Select bit
                sta     DSP
                ora     #E            ; Set Enable bit
                sta     DSP
                eor     #E            ; Clear Enable bit
                sta     DSP
                pla
                and     #%00001111    ; Mask LSD
                ora     #RS           ; Set Register Select bit
                sta     DSP
                ora     #E            ; Set Enable bit
                sta     DSP
                eor     #E            ; Clear Enable bit
                sta     DSP
                jsr     lcd_wait      ; Wait for Display
                rts

lcd_scroll:
                lda     #%10101000    ; put cursor on next line
                jsr     lcd_inst
                rts

lcd_home:
                lda     #%00000010    ; move the cursor to home
                jsr     lcd_inst
                lda     #PROMPT       ; Print the prompt
                jsr     lcd_echo
                rts

lcd_wait:
                pha
                lda     #%11110000    ; Set LCD register to input mode
                sta     DSPDR
lcd_busy:
                lda     #RW           ; Set Read bit
                sta     DSP
                lda     #(RW | E)     ; Set Enable bit
                sta     DSP
                lda     DSP           ; Read high nibble
                pha                   ; push on stack since it has the busy flag
                lda     #RW
                sta     DSP
                lda     #(RW | E)
                sta     DSP
                lda     DSP           ; Read low nibble
                pla                   ; Get high nibble off stack
                and     #%00001000    ; Mask busy bit
                bne     lcd_busy      ; Still busy.

                lda     #RW
                sta     DSP
                lda     #%11111111    ; Set LCD register to output mode
                sta     DSPDR
                pla
                rts

nmi:
                rti

irq:
                jsr     nextchar      ; key pressed!
                rti

.segment "VECTORS"
                .word   nmi
                .word   reset
                .word   irq

