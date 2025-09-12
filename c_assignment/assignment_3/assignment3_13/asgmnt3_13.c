#include <stdio.h>

int product(int a, int b) {
    int res = 0;
    for (int i = 0; i < b; i++) {
        res += a;
    }
    return res;
}

int main() {
    int x, y;
    printf("Enter two numbers: ");
    scanf("%d %d", &x, &y);
    printf("Product = %d\n", product(x, y));
    return 0;
}

