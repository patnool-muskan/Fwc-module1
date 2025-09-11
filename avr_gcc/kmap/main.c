#include <avr/io.h>
int W, X, Y, Z;
int A, B, C, D;

void disp_7447(int D, int C, int B, int A){
    PORTD &= ~(0x3C);           // 0b00111100
    PORTD |= (A<<2) | (B<<3) | (C<<4) | (D<<5);
}

int main(void){
    DDRD |= 0x3C;  
    DDRB = 0x00;

    while(1){
        W = (PINB & (1<<PB0)) ? 1 : 0;
        X = (PINB & (1<<PB1)) ? 1 : 0;
        Y = (PINB & (1<<PB2)) ? 1 : 0;
        Z = (PINB & (1<<PB3)) ? 1 : 0;

        A = (!W && !Z) || (!W && !X && !Y);
        B = (W && !X && !Z) || (!W && X && !Z);
        C = (W && X && !Y && !Z) || (!X && Y && !Z) || (!W && Y && !Z);
        D = (W && X && Y && !Z) || (!W && !X && !Y && Z);

        disp_7447(D, C, B, A);
    }
}

