#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    int X, Y, Z;      // current state inputs (from flip-flop Q outputs)
    int A, B, C;       // next state inputs (to D inputs)
    int F;            // logic output

    // Configure inputs: X = PD4, Y = PD3, Z = PD2
    DDRD &= ~((1<<PD2)|(1<<PD3)|(1<<PD4));

    // Configure outputs: A = PB0, B = PB1, C = PB2, F = PB3, CLK = PB4
    DDRB |= (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)|(1<<PB4);

    while (1) {
        // Read current state (from flip-flops)
        Z = (PIND & (1<<PD2)) ? 1 : 0; // LSB
        Y = (PIND & (1<<PD3)) ? 1 : 0;
        X = (PIND & (1<<PD4)) ? 1 : 0; // MSB

        // === FSM next-state logic ===
        // Next state = current + 1 (mod 8)
        int state = (X << 2) | (Y << 1) | Z;
        state = (state + 1) % 8;

        // Decompose next state
        C = (state >> 2) & 1; // MSB
        B = (state >> 1) & 1;
        A = state & 1;        // LSB

        // === Logic Gate Output: NOR(X, Y) ===
        F = !(X | Y);   // Only X and Y used in NOR

        // === Output to 7447 (BCD input) ===
        // Send F as LSB (PB3), others 0
        if(F) PORTB |= (1<<PB3); else PORTB &= ~(1<<PB3); // F → PB3

        // === Output next state to D inputs ===
        if(A) PORTB |= (1<<PB0); else PORTB &= ~(1<<PB0); // A → PB0
        if(B) PORTB |= (1<<PB1); else PORTB &= ~(1<<PB1); // B → PB1
        if(C) PORTB |= (1<<PB2); else PORTB &= ~(1<<PB2); // C → PB2

        // === Toggle clock to latch D → Q ===
        PORTB |= (1<<PB4);   // CLK HIGH
        _delay_ms(500);
        PORTB &= ~(1<<PB4);  // CLK LOW
        _delay_ms(500);
    }
}
