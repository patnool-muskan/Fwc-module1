;===============================================
; AVR Assembly: A & ~B shown on 7-seg (via 7447)
; Using 7474 flip-flops as storage
;===============================================

.include "m328Pdef.inc"

; Pin definitions (bit masks)
.equ CLOCK_PIN = 0x04    ; PD2 = bit2
.equ D_A       = 0x20    ; PD5 = bit5
.equ D_B       = 0x40    ; PD6 = bit6
.equ Q_A_MASK  = 0x08    ; PD3 = bit3
.equ Q_B_MASK  = 0x10    ; PD4 = bit4

;-----------------------------------------------
; Reset Vector
;-----------------------------------------------
.cseg
.org 0x00
rjmp RESET

RESET:
    ; Set CLOCK, D_A, D_B as output
    ldi r16, CLOCK_PIN | D_A | D_B
    out DDRD, r16

    ; Enable pull-ups on Q_A, Q_B
    ldi r16, Q_A_MASK | Q_B_MASK
    out PORTD, r16        

    ; Set PB0-PB3 as output
    ldi r16, 0x0F
    out DDRB, r16

;-----------------------------------------------
; Main Loop
;-----------------------------------------------
MAIN_LOOP:

    ; Example: A = 1, B = 0
    in r16, PORTD
    ori r16, D_A        ; set D_A = 1
    andi r16, 0xBF      ; clear bit6 (D_B = 0), 0xBF = 10111111
    out PORTD, r16

    ; Latch into 7474 flip-flops (clock pulse)
    in r16, PORTD
    ori r16, CLOCK_PIN
    out PORTD, r16
    rcall DELAY_SHORT

    in r16, PORTD
    andi r16, 0xFB      ; clear bit2 (CLOCK low), 0xFB = 11111011
    out PORTD, r16
    rcall DELAY_SHORT

    ; Read Q_A, Q_B from PIND
    in r17, PIND

    ; extract Q_A (PD3)
    mov r18, r17
    lsr r18
    lsr r18
    lsr r18
    andi r18, 0x01      ; A_in in bit0

    ; extract Q_B (PD4)
    mov r19, r17
    lsr r19
    lsr r19
    lsr r19
    lsr r19
    andi r19, 0x01      ; B_in in bit0

    ; Q = A & ~B
    com r19
    andi r19, 0x01
    and r18, r19        ; r18 = Q

    ; Output Q to PORTB (low nibble)
    in r20, PORTB
    andi r20, 0xF0
    or r20, r18
    out PORTB, r20

    rcall DELAY_LONG
    rjmp MAIN_LOOP

;-----------------------------------------------
; Delay routines (approximate)
;-----------------------------------------------
DELAY_SHORT:               ; ~1ms
    ldi r21, 0xFF
D1: dec r21
    brne D1
    ret

DELAY_LONG:                ; ~200ms
    ldi r22, 200
DL1: rcall DELAY_SHORT
    dec r22
    brne DL1
    ret
