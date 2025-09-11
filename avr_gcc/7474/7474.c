#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB |= (1 << PB5);
    DDRB |= (1 << PB0);

    DDRD &= ~(1 << PD7);

    PORTB |= (1 << PB0);

    while(1) {
        int q_not = (PIND & (1 << PD7)) ? 1 : 0;
        if (q_not)
            PORTB |= (1 << PB0);  // D HIGH
        else
            PORTB &= ~(1 << PB0); // D LOW

        PORTB |= (1 << PB5);
        _delay_ms(500);

        PORTB &= ~(1 << PB5);
        _delay_ms(500);
    }
}
