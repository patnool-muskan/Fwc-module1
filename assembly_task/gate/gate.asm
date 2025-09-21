; Assembly program to implement Q = A AND (NOT B)
; Inputs: A = PD0, B = PD1
; Output: Q = PB0

.include "m328Pdef.inc"

ldi r16, 0b00000001      ; Set PB0 as output
out DDRB, r16

ldi r16, 0b00000000      ; Set PORTD as input
out DDRD, r16

loop:
    in r17, PIND          ; Read inputs from PORTD
    mov r18, r17          ; Copy input
    andi r18, 0b00000001  ; Extract A (bit0) → r18
    
    mov r19, r17
    lsr r19               ; Shift right → B is now bit0
    andi r19, 0b00000001  ; Extract B
    
    com r19               ; Invert B
    andi r19, 0x01        ; Keep only 1 bit
    
    and r18, r19          ; A AND (NOT B) → result in r18
    
    out PORTB, r18        ; Send Q to PB0
    
    rjmp loop             ; Repeat forever
