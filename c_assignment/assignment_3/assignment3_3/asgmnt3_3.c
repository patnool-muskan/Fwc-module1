#include <stdio.h>

void Swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    printf("After swapping: a=%d, b=%d\n", a, b);
}

int main() {
    int x = 10, y = 20;
    Swap(x, y);
    return 0;
}

