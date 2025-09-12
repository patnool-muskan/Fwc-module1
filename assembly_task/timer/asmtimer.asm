.include "m328Pdef.inc"

; ---------------------------------------------------
; Inputs : A=PD5, B=PD4
; Outputs: PB0 → Output Q (to 7447 input A)
;          PB5 → CLK for 7474 (~1 Hz square wave)
; ---------------------------------------------------

.org 0x00
rjmp reset

reset:
    ; Configure inputs: PD5 (A), PD4 (B) as input
    ldi r16, 0x00
    out DDRD, r16

    ; Configure outputs: PB0 (Q), PB5 (CLK) as output
    ldi r16, (1<<DDB0)|(1<<DDB5)
    out DDRB, r16

    ; Setup Timer0 with prescaler 1024 for ~1Hz clock generation
    ldi r16, 0b00000101      ; CS02=1, prescaler=1024
    out TCCR0B, r16
    clr r18                  ; temp register

main:
    ; Read inputs A and B from PIND
    in r16, PIND
    ; Extract A (PD5) and B (PD4)
    sbrc r16, 5              ; Skip next instruction if bit 5 (A) is cleared
    ldi r17, 1               ; A = 1
    sbrs r16, 5
    ldi r17, 0               ; A = 0 if PD5 is 0

    sbrc r16, 4              ; Skip next if bit 4 (B) cleared
    ldi r19, 1               ; B = 1
    sbrs r16, 4
    ldi r19, 0               ; B = 0 if PD4 is 0

    ; -------- Compute Q as per circuit (A) --------
    ; Circuit (A):
    ; Q = (A OR B) AND (NOT B)
    ; So Q = (A + B) * (~B)

    ; Compute A OR B
    mov r20, r17
    or r20, r19

    ; Compute NOT B
    ldi r21, 1
    eor r21, r19      ; r21 = ~B

    ; Compute Q = (A + B) & (~B)
    and r20, r21      ; r20 = Q

    ; Output Q on PB0
    ; First clear PB0
    cbi PORTB, 0
    ; If Q = 1 set PB0
    tst r20
    breq skip_set_pb0
    sbi PORTB, 0
skip_set_pb0:

    ; Toggle clock on PB5 using timer delay (~500 ms HIGH, 500 ms LOW)

    sbi PORTB, 5      ; Set PB5 HIGH
    rcall delay500_timer

    cbi PORTB, 5      ; Set PB5 LOW
    rcall delay500_timer

    rjmp main

; ---------------------------------------------------
; Timer0-based delay ~500 ms
; ---------------------------------------------------
delay500_timer:
    ldi r19, 0b01000000       ; outer loop count
lp2:
    in r16, TIFR0             ; read Timer0 interrupt flag
    ldi r17, 0b00000010       ; TOV0 bit mask
    and r16,r17
    breq lp2                  ; wait until TOV0 flag is set
    out TIFR0, r17            ; clear overflow flag
    dec r19
    brne lp2
    ret
