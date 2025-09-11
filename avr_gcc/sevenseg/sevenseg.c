//Prints a decimal number 
//on the display
#include <avr/io.h>
#include <util/delay.h> 
int main (void)
{
 
 
 //set PD2-PD7 as output pins 0xFC=0b11111100 (binary)
  DDRD   |= 0xFC;
  //set PB0 as output pin
  DDRB    |= ((1 << DDB0));
 
  while (1) {
    PORTB = ((1 <<  PB0));
    PORTD = 0b11100100;
    _delay_ms(500);
    PORTB = 0x00;
    PORTD = 0b10010000;
    _delay_ms(500);
    PORTB = 0x00;
    PORTD = 0b11000000;
    _delay_ms(500);
    PORTB = 0x00;
    PORTD = 0b01100100;
    _delay_ms(500);
    PORTB = 0x00;
    PORTD = 0b01001000;
    _delay_ms(500);
    PORTB = 0x00;
    PORTD = 0b00001000;
    _delay_ms(500);
    PORTB = ((1 <<  PB0));
    PORTD = 0b11100000;
    _delay_ms(500);
    PORTB = 0x00;
    PORTD = 0b00000000;
    _delay_ms(500);
    PORTB = 0x00;
    PORTD = 0b01000000;
    _delay_ms(500);
    PORTB = 0x01;
    PORTD = 0b00000000;
    _delay_ms(500);


  }

  /* . */
  return 0;

}
