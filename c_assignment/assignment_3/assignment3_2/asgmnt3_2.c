#include <stdio.h>

int Add(int a, int b) { return a + b; }
int Sub(int a, int b) { return a - b; }
int Mul(int a, int b) { return a * b; }
int Div(int a, int b) { return b != 0 ? a / b : 0; }
int Mod(int a, int b) { return b != 0 ? a % b : 0; }

int main() {
    int x = 20, y = 6;
    printf("Add = %d\n", Add(x, y));
    printf("Sub = %d\n", Sub(x, y));
    printf("Mul = %d\n", Mul(x, y));
    printf("Div = %d\n", Div(x, y));
    printf("Mod = %d\n", Mod(x, y));
    return 0;
}

