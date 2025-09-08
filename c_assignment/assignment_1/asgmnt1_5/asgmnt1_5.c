#include <stdio.h>

int* staticFunc() {
    static int value = 0;

    if (value != 0) {
        printf("Square: %d\n", value * value);
    }

    return &value; // return address of static variable
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int *ptr;

    for (int i = 0; i < 5; i++) {
        ptr = staticFunc();   // get address of static variable
        *ptr = arr[i];        // main puts array element into static variable
        staticFunc();         // call again to print square
    }

    return 0;
}

