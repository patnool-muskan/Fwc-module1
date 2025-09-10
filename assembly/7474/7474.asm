.include "m328Pdef.inc"

ldi r16, 00100000      ; make CLK output
out DDRB, r16

ldi r17, 10000000        ; make D output (for init)
out DDRD, r17

sbi PORTD,7   ; set D = 1
sbi PORTB,5
rcall delay_10ms
cbi PORTB, 5
rcall delay_10ms
cbi PORTD,7
loop:
    sbi PORTB, 5
    rcall delay_500ms
    cbi PORTB, 5
    rcall delay_500ms
    rjmp loop

delay_10ms:
    ldi r18, 5
d10_loop:
    ldi r19, 200
d10_inner:
    ldi r20, 200
d10_inner2:
    dec r20
    brne d10_inner2
    dec r19
    brne d10_inner
    dec r18
    brne d10_loop
    ret
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
