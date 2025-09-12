#include <stdio.h>

float totalAmount(float principle, float rate, int months) {
    float timeInYears = months / 12.0;
    float si = (principle * rate * timeInYears) / 100.0;
    return principle + si;
}

int main() {
    float p, r;
    int t;
    printf("Enter Principle, Rate, Time (in months): ");
    scanf("%f %f %d", &p, &r, &t);
    printf("Total amount to be repaid = %.2f\n", totalAmount(p, r, t));
    return 0;
}

