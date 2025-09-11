.include "m328Pdef.inc"

;------------------------------------------------
; Initialization
;------------------------------------------------
    ldi r16, (1<<PD3)|(1<<PD4)   ; enable pull-ups on PD3, PD4
    out PORTD, r16

    ldi r16, 0x00
    out DDRD, r16                ; PD3, PD4 as inputs

    ldi r16, 0x0F
    out DDRB, r16                ; PB0–PB3 as outputs

;------------------------------------------------
; Main Loop
;------------------------------------------------
loop:
    ; Read PIND
    in r17, PIND

    ; Extract A = PD3
    mov r18, r17
    lsr r18                      ; shift >>1 (PD2→carry, PD3→PD2)
    lsr r18                      ; shift >>2
    lsr r18
    andi r18, 0x01               ; keep only bit0
    ; r18 now = A (0/1)

    ; Extract B = PD4
    mov r19, r17
    lsr r19
    lsr r19
    lsr r19
    lsr r19
    andi r19, 0x01               ; keep only bit0
    ; r19 now = B (0/1)

    ; NOT B
    com r19
    andi r19, 0x01

    ; Q = A AND NOT B
    and r18, r19                 ; r18 = Q (0/1)

    ; Output Q on PB0–PB3
    in r20, PORTB
    andi r20, 0xF0               ; clear PB0–PB3
    or r20, r18                  ; put Q in bit0
    out PORTB, r20

    rjmp loop
