#include <stdio.h>

// Structure for arithmetic results
struct Results {
    int sum;
    int diff;
    int prod;
    float quot;
    int rem;
};

// Function to calculate results
struct Results calculate(int a, int b) {
    struct Results r;
    r.sum = a + b;
    r.diff = a - b;
    r.prod = a * b;
    r.quot = (float)a / b;
    r.rem = a % b;
    return r;
}

int main() {
    int x, y;
    printf("Enter two integers: ");
    scanf("%d %d", &x, &y);

    struct Results res = calculate(x, y);

    printf("Addition = %d\n", res.sum);
    printf("Subtraction = %d\n", res.diff);
    printf("Multiplication = %d\n", res.prod);
    printf("Quotient = %.2f\n", res.quot);
    printf("Remainder = %d\n", res.rem);

    return 0;
}

