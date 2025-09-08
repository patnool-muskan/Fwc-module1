#include <stdio.h>

// Declaration of swap function from swap.c
void swap(int *a, int *b);

int main() {
    int arr[2] = {5, 10};

    printf("Before swap: %d %d\n", arr[0], arr[1]);
    swap(&arr[0], &arr[1]);
    printf("After swap: %d %d\n", arr[0], arr[1]);

    return 0;
}

