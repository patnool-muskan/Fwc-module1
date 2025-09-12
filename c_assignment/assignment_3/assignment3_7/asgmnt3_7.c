#include <stdio.h>

int power(int a, int n) {
    int res = 1;
    for (int i = 0; i < n; i++)
        res *= a;
    return res;
}

int main() {
    int a, n;
    printf("Enter a and n: ");
    scanf("%d %d", &a, &n);
    printf("%d^%d = %d\n", a, n, power(a, n));
    return 0;
}

