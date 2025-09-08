#include <stdio.h>

// Call by Value
void swapByValue(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    printf("Inside swapByValue: a=%d, b=%d\n", a, b);
}

// Call by Reference
void swapByReference(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    printf("Inside swapByReference: a=%d, b=%d\n", *a, *b);
}

int main() {
    int x = 5, y = 10;

    printf("Before swap: x=%d, y=%d\n", x, y);

    swapByValue(x, y);
    printf("After swapByValue: x=%d, y=%d \n", x, y);

    swapByReference(&x, &y);
    printf("After swapByReference: x=%d, y=%d \n", x, y);

    return 0;
}

