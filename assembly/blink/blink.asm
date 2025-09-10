;hello
;using assembly language for turning LED on


.include "m328Pdef.inc"


  ldi r16,0b00000001
  out DDRB,r16
 loop: 
  ldi r17,0b00000001
 out PortB,r17
 ldi r18, 255
delay_on:
 nop
 dec r18
 brne delay_on
ldi r18, 255
delay_on1:
        nop
        dec r18
        brne delay_on1
ldi r18, 255
delay_on2:
        nop
        dec r18
        brne delay_on2
ldi r17,0b00000000
ldi r18,255
delay_off:
 nop
 dec r18
 brne delay_off
ldi r18,255
delay_off1:
        nop
        dec r18
        brne delay_off1
ldi r18,255
delay_off2:
        nop
        dec r18
        brne delay_off2
rjmp loop
