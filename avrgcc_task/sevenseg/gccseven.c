#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// Segment pins for 7-segment display (common-anode)
#define SEG_A PB0  // D8
#define SEG_B PB1  // D9
#define SEG_C PB2  // D10
#define SEG_D PB3  // D11
#define SEG_E PB4  // D12
#define SEG_F PB5  // D13
#define SEG_G PD2  // D2

// Function to display 0 or 1 on common-anode 7-segment
void display_digit(uint8_t digit) {
    // Turn OFF all segments first (HIGH for common-anode)
    PORTB |= (1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F);
    PORTD |= (1<<SEG_G);
    
    switch(digit) {
        case 0: // segments a b c d e f ON (LOW)
            PORTB &= ~((1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F));
            break;
        case 1: // segments b c ON (LOW)
            PORTB &= ~((1<<SEG_B)|(1<<SEG_C));
            break;
    }
}

int main(void) {
    // --- Configure inputs PD3 (A) and PD4 (B) ---
    DDRD &= ~((1<<PD3) | (1<<PD4));  // set as input
    PORTD |= (1<<PD3) | (1<<PD4);    // enable internal pull-ups

    // --- Configure outputs for 7-segment ---
    DDRB |= (1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F); // PB0–PB5
    DDRD |= (1<<SEG_G); // PD2

    while(1) {
        // --- Read inputs ---
        uint8_t A = (PIND & (1<<PD3)) >> PD3;
        uint8_t B = (PIND & (1<<PD4)) >> PD4;

        // --- Logic gate ---
        uint8_t Q = A & ~B; // Q = A AND NOT B

        // --- Display on 7-segment ---
        display_digit(Q);

        _delay_ms(200);
    }
}
