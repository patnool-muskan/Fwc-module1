.include "m328Pdef.inc"

.org 0x00
    rjmp reset

reset:
    ; ---------- Setup I/O ----------
    ldi r16, 0x00
    out DDRD, r16          ; PD0=A, PD1=B as input

    ldi r16, (1<<DDB0)     ; PB0 as output (LED/Q)
    out DDRB, r16

    ; ---------- Store Q truth table ----------
    ; Index = (A*2 + B) → 0..3
    ldi r16,0              ; F(0)=0
    sts 0x60,r16
    ldi r16,0              ; F(1)=0
    sts 0x61,r16
    ldi r16,1              ; F(2)=1 (A=1,B=0)
    sts 0x62,r16
    ldi r16,0              ; F(3)=0
    sts 0x63,r16

main:
    ; ---------- Read inputs ----------
    in r16,PIND
    andi r16,0x03          ; keep PD0, PD1 (A,B)
    
    ; ---------- Lookup from SRAM ----------
    ldi r30,0x60           ; base address of table
    ldi r31,0x00
    add r30,r16            ; add index (0–3)
    ld r17,Z               ; fetch Q
    
    ; ---------- Output to PB0 ----------
    andi r17,0x01
    out PORTB,r17

    rjmp main
