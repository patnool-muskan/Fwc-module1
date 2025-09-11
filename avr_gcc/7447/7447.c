#include <avr/io.h>
int A, B, C, D;
int W, X, Y, Z;

void disp_7447(int D, int C, int B, int A){
    PORTD &= ~(0x3C);  // 0b00111100
    PORTD |= (A<<2) | (B<<3) | (C<<4) | (D<<5);
}

int main(void){
    DDRD |= 0x3C;  // 0b00111100
    DDRB = 0x00;   // All PB pins input
    while(1){
        W = (PINB & (1<<PB0)) ? 1 : 0;
        X = (PINB & (1<<PB1)) ? 1 : 0;
        Y = (PINB & (1<<PB2)) ? 1 : 0;
        Z = (PINB & (1<<PB3)) ? 1 : 0;
        A = (!W && !X && !Y && !Z) || (!W && X && !Y && !Z) || (!W && !X && Y && !Z) || (!W && X && Y && !Z) || (!W && !X && !Y && Z);
        B = (W && !X && !Y && !Z) || (!W && X && !Y && !Z) || (W && !X && Y && !Z) || (!W && X && Y && !Z);
        C = (W && X && !Y && !Z) || (!W && !X && Y && !Z) || (W && !X && Y && !Z) || (!W && X && Y && !Z);
        D = (W && X && Y && !Z) || (!W && !X && !Y && Z);
        disp_7447(D,C,B,A);
    }
}
