#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define CLOCK_PIN PD2
#define D_A PD5
#define D_B PD6
#define Q_A PD3   // read Q1 from 7474
#define Q_B PD4   // read Q2 from 7474

int main(void) {
    // --- Configure Arduino pins ---
    DDRD |= (1<<CLOCK_PIN) | (1<<D_A) | (1<<D_B); // outputs
    DDRD &= ~((1<<Q_A) | (1<<Q_B));               // inputs (from 7474)
    PORTD |= (1<<Q_A) | (1<<Q_B);                 // enable pull-ups

    DDRB |= 0x0F;   // PB0–PB3 outputs to 7447

    while (1) {
        // Example: set A=1, B=0
        PORTD |= (1<<D_A);   // A = 1
        PORTD &= ~(1<<D_B);  // B = 0

        // Latch into flip-flops
        PORTD |= (1<<CLOCK_PIN);
        _delay_ms(1);
        PORTD &= ~(1<<CLOCK_PIN);

        // Read back A, B from 7474
        uint8_t A_in = (PIND & (1<<Q_A)) >> Q_A;
        uint8_t B_in = (PIND & (1<<Q_B)) >> Q_B;

        // Logic Q = A AND NOT B
        uint8_t Q = A_in & (~B_in & 0x01);

        // Drive 7447 (0 or 1)
        PORTB = (PORTB & 0xF0) | (Q & 0x0F);

        _delay_ms(500);
    }
}
