.include "m328Pdef.inc"

; ---------------------------------------
; Pin mapping (using full port separation)
; ---------------------------------------
.equ A   = 0        ; PB0
.equ B   = 1        ; PB1
.equ C   = 2        ; PB2
.equ D   = 3        ; PB3
.equ CLK = 5        ; PB5

.equ W   = 0        ; PD0
.equ X   = 1        ; PD1
.equ Y   = 2        ; PD2
.equ Z   = 3        ; PD3

; ---------------------------------------
; Setup
; ---------------------------------------
ldi r16, (1<<A)|(1<<B)|(1<<C)|(1<<D)|(1<<CLK) ; PB0..PB3, PB5 = output
out DDRB, r16

ldi r16, 0x00        ; All Port D = input
out DDRD, r16

; ---------------------------------------
; Main Loop
; ---------------------------------------
loop:
    ; --- Read inputs from Port D ---
    in r17, PIND       ; r17 = PIND (W,X,Y,Z on PD0..PD3)

    ; Extract bits into single registers
    mov r18, r17       ; W
    andi r18, (1<<W)
    lsr r18            ; r18 = W in bit0

    mov r19, r17       ; X
    andi r19, (1<<X)
    lsr r19
    lsr r19            ; r19 = X in bit0

    mov r20, r17       ; Y
    andi r20, (1<<Y)
    lsr r20
    lsr r20
    lsr r20            ; r20 = Y in bit0

    mov r21, r17       ; Z
    andi r21, (1<<Z)
    lsr r21
    lsr r21
    lsr r21
    lsr r21            ; r21 = Z in bit0

    ; ---------------------------------------
    ; Logic equations
    ; ---------------------------------------

    ; A = !W
    com r18
    andi r18, 0x01     ; r18 = A

    ; B = (W && !X && !Z) || (!W && X)
    mov r22, r19       ; X
    com r22
    andi r22, 0x01     ; !X

    mov r23, r21       ; Z
    com r23
    andi r23, 0x01     ; !Z

    mov r24, r18       ; !W (we saved only A, so recompute)
    com r24
    andi r24, 0x01     ; W

    mov r25, r24       ; W
    and r25, r22       ; W && !X
    and r25, r23       ; W && !X && !Z

    mov r26, r18       ; !W
    and r26, r19       ; !W && X

    or r25, r26
    mov r19, r25       ; r19 = B

    ; C = (!X && Y)  (!W && Y)  (W && X && !Y)
    mov r22, r19
    com r22
    andi r22,0x01      ; !X
    mov r23,r22
    and r23,r20        ; !X && Y

    mov r24,r18        ; !W
    and r24,r20        ; !W && Y

    mov r25,r24        ; W
    and r25,r19        ; W && X
    com r20
    andi r20,0x01      ; !Y
    and r25,r20        ; W && X && !Y

    or r23,r24
    or r23,r25
    mov r20,r23        ; r20 = C

    ; D = (!W && Z) || (W && X && Y)
    mov r22,r18        ; !W
    and r22,r21        ; !W && Z

    mov r23,r24        ; W
    and r23,r19        ; W && X
    and r23,r20        ; W && X && Y

    or r22,r23
    mov r21,r22        ; r21 = D

    ; ---------------------------------------
    ; Build output byte (shift+OR method)
    ; ---------------------------------------
    ; r18 = A, r19 = B, r20 = C, r21 = D
    clr r30            ; r30 = 0

    ; put A into bit0
    or r30, r18

    ; put B into bit1
    lsl r19
    or r30, r19

    ; put C into bit2
    lsl r20
    lsl r20
    or r30, r20

    ; put D into bit3
    lsl r21
    lsl r21
    lsl r21
    or r30, r21

    ; Write outputs A..D
    in r31, PORTB
    andi r31, 0b11110000     ; clear PB0..PB3
    or r31, r30
    out PORTB, r31

    ; ---------------------------------------
    ; Blink LED on PB5
    ; ---------------------------------------
    sbi PORTB, CLK
    rcall delay_500ms
    cbi PORTB, CLK
    rcall delay_500ms

    rjmp loop

; ---------------------------------------
; Delay ~500 ms
; ---------------------------------------
delay_500ms:
    ldi r18, 40
outer:
    ldi r19, 200
inner:
    ldi r20, 200
inner2:
    dec r20
    brne inner2
    dec r19
    brne inner
    dec r18
    brne outer
    ret
