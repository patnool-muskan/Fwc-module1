#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // --- Configure inputs PD3 (A) and PD4 (B) with pull-ups ---
    DDRD &= ~((1<<PD3) | (1<<PD4));  // set PD3, PD4 as input
    PORTD |= (1<<PD3) | (1<<PD4);    // enable internal pull-ups

    // --- Configure outputs PB0-PB3 for 7447 BCD inputs A-D ---
    DDRB |= 0x0F; // PB0-PB3 as output

    while(1) {
        // --- Read inputs ---
        uint8_t A_in = (PIND & (1<<PD3)) >> PD3;
        uint8_t B_in = (PIND & (1<<PD4)) >> PD4;

        // --- Logic gate: Q = A AND NOT B ---
        uint8_t Q = A_in & ~B_in;

        // --- Output Q to 7447 ---
        // 7447 BCD inputs: A = LSB, D = MSB
        // Since we only need 0 or 1, other bits stay 0
        PORTB = (PORTB & 0xF0) | (Q & 0x0F); // PB0-PB3 -> 7447 inputs A-D

        _delay_ms(200);
    }
}
