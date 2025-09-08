#include <stdio.h>

void rotate(int *a, int *b, int *c) {
    int temp = *a;
    *a = *b;
    *b = *c;
    *c = temp;
}

int main() {
    int x = 1, y = 2, z = 3;

    printf("Before rotation: x=%d, y=%d, z=%d\n", x, y, z);

    rotate(&x, &y, &z);

    printf("After rotation: x=%d, y=%d, z=%d\n", x, y, z);

    return 0;
}

