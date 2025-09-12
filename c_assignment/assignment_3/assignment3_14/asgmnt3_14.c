#include <stdio.h>

int square(int n) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        res += n;
    }
    return res;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Square = %d\n", square(num));
    return 0;
}

