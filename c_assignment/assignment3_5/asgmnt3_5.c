#include <stdio.h>

int IsPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

void PrintAllPrimes(int start, int end) {
    for (int i = start; i <= end; i++) {
        if (IsPrime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int a, b;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);
    PrintAllPrimes(a, b);
    return 0;
}

