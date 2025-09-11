#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3);

    DDRB |= (1 << PB5);

    DDRD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5));

    while (1) {
        int W = (PIND & (1 << PD2)) ? 1 : 0;
        int X = (PIND & (1 << PD3)) ? 1 : 0;
        int Y = (PIND & (1 << PD4)) ? 1 : 0;
        int Z = (PIND & (1 << PD5)) ? 1 : 0;

        int A = (!W);
        int B = (W && !X && !Z) || (!W && X);
        int C = (!X && Y) || (!W && Y) || (W && X && !Y);
        int D = (!W && Z) || (W && X && Y);

        if (A) PORTB |= (1 << PB0); else PORTB &= ~(1 << PB0);
        if (B) PORTB |= (1 << PB1); else PORTB &= ~(1 << PB1);
        if (C) PORTB |= (1 << PB2); else PORTB &= ~(1 << PB2);
        if (D) PORTB |= (1 << PB3); else PORTB &= ~(1 << PB3);

        PORTB |= (1 << PB5);
        _delay_ms(500);
        PORTB &= ~(1 << PB5);
        _delay_ms(500);
    }
}

