#include <stdio.h>

void calculate(int a, int b, int *sum, int *diff, int *prod, int *quot, int *rem) {
    *sum = a + b;
    *diff = a - b;
    *prod = a * b;
    *quot = a / b;
    *rem = a % b;
}

int main() {
    int a = 20, b = 6;
    int sum, diff, prod, quot, rem;

    calculate(a, b, &sum, &diff, &prod, &quot, &rem);

    printf("Addition: %d\n", sum);
    printf("Subtraction: %d\n", diff);
    printf("Multiplication: %d\n", prod);
    printf("Quotient: %d\n", quot);
    printf("Remainder: %d\n", rem);

    return 0;
}

