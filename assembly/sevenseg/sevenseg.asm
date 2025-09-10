;using assembly language for 
;displaying number on
;seven segment display

.include "m328Pdef.inc"

  
;Configuring pins 2-7 (PD2-PD7) of Arduino
;as output
 ; ldi r16,0b11111100
;  out DDRD,r16
;Configuring pin 8 (PB0) of Arduino
;as output 
;  ldi r16,0b00000001
;  out DDRB,r16
;Writing the number 2 on the 
;seven segment display
 ; ldi r17,0b11100100
;  out PortD,r17
  
;  ldi r17,0b00000001
;  out PortB,r17
;Start:
;  rjmp Start



;0-9 loop

; Setup
ldi r16, 0b11111100      ; PD2–PD7 as output
out DDRD, r16

ldi r16, 0b00000001      ; PB0 as output
out DDRB, r16

LoopDigits:
   ; Display 0
    ldi r17, 0b00000011
    out PORTD, r17
ldi r16,0b00000001
out PORTB,r16
    rcall Delay

    ; Display 1
    ldi r17, 0b11100111
    out PORTD, r17
ldi r16,0b00000001
out PORTB,r16
    rcall Delay

    ; Display 2
    ldi r17, 0b10010011
    out PORTD, r17
ldi r16,0b00000000
out PORTB,r16
    rcall Delay

    ; Display 3
    ldi r17, 0b11000011
    out PORTD, r17
ldi r16,0b00000000
out PORTB,r16
    rcall Delay

    ; Display 4
    ldi r17, 0b01100111
    out PORTD, r17
ldi r16,0b00000000
out PORTB,r16
    rcall Delay

    ; Display 5
    ldi r17, 0b01001011
    out PORTD, r17
ldi r16,0b00000000
out PORTB,r16
    rcall Delay

    ; Display 6
    ldi r17, 0b00001011
    out PORTD, r17
ldi r16,0b00000000
out PORTB,r16
    rcall Delay

    ; Display 7
    ldi r17, 0b11100011
    out PORTD, r17
ldi r16,0b00000001
out PORTB,r16
    rcall Delay

    ; Display 8
    ldi r17, 0b00000011
    out PORTD, r17
ldi r16,0b00000000
out PORTB,r16
    rcall Delay

    ; Display 9
    ldi r17, 0b01000011
    out PORTD, r17
ldi r16,0b00000000
out PORTB,r16
    rcall Delay

    rjmp LoopDigits

; Long Delay Routine
Delay:
    ldi r18, 0xFF        ; Outer loop
DelOuter:
    ldi r19, 0xFF        ; Middle loop
DelMiddle:
    ldi r20, 0xFF        ; Inner loop
DelInner:
    dec r20
    brne DelInner
    dec r19
    brne DelMiddle
    dec r18
    brne DelOuter
    ret
