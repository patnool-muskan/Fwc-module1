.include "m328Pdef.inc"

.org 0x0000
    rjmp reset

reset:
    ; -------- Setup I/O --------
    ldi r16, 0x00
    out DDRD, r16        ; PD0=A, PD1=B as input

    ldi r16, (1<<DDB0)   ; PB0 as output
    out DDRB, r16

main:
    ; -------- Read Inputs --------
    in r16, PIND
    andi r16, 0x03       ; keep PD0 (A) and PD1 (B)

    ; Extract A
    mov r17, r16
    andi r17, 0x01       ; A = bit0

    ; Extract B
    mov r18, r16
    lsr r18              ; shift right → bit0 = B
    andi r18, 0x01       ; B

    ; Compute ~B
    ldi r19, 1
    eor r19, r18         ; r19 = ~B

    ; Compute Q = A·~B
    mov r20, r17
    and r20, r19

    ; Output Q
    andi r20,0x01
    out PORTB,r20

    rjmp main
