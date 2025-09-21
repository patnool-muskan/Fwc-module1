.include "m328Pdef.inc"
ldi r16, 0xFF        ; Set PORTD (pins 0–7) as output (7-seg display)
out DDRD, r16

ldi r16, 0x00        ; Set PORTB as input (A,B from PB0, PB1)
out DDRB, r16

loop:
    in r17, PINB          ; Read PORTB
    mov r18, r17          ; Copy to r18
    andi r18, 0x03        ; Mask only PB0 (A), PB1 (B)

    ; Extract A and B
    mov r19, r18          ; r19 = A,B
    lsr r19               ; Shift right → r19 = A
    andi r19, 0x01        ; A = bit0
    mov r20, r18
    andi r20, 0x01        ; B = bit0

    ; Invert B → ~B
    ldi r21, 0x01
    eor r20, r21          ; B = NOT B

    ; Compute Q = A AND ~B
    and r19, r20          ; Q = A * ~B
    mov r22, r19          ; Store Q

    cpi r22, 0
    breq showZero         ; if Q=0 → show 0
    rjmp showOne          ; if Q=1 → show 1

showZero:
    ldi r23, 0b00111111   ; pattern for "0"
    out PORTD, r23
    rjmp loop

showOne:
    ldi r23, 0b00000110   ; pattern for "1"
    out PORTD, r23
    rjmp loop
