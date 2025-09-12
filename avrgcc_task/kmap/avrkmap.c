#include <avr/io.h>

int main(void) {
    // Inputs: A = PD3, B = PD2
    DDRD &= ~((1<<PD2) | (1<<PD3));  // Set PD2, PD3 as input

    // Outputs: PB0 (LSB) to PB3 (MSB) go to 7447 A-D inputs
    DDRB |= 0x0F;  // Set PB0–PB3 as output

    int A, B, F;

    while (1) {
        // Read inputs
        B = (PIND & (1<<PD2)) ? 1 : 0;
        A = (PIND & (1<<PD3)) ? 1 : 0;

        // Example Gate: NOR => F = !(A | B)
        F = !(A | B);

        // Output F on PB0, and 0s on PB1–PB3 (BCD format)
        PORTB = (PORTB & 0xF0) | (F & 0x01);  // Set PB0=F, PB1–PB3=0
    }
}
