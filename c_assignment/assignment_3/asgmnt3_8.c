#include <stdio.h>

int isLeapYear(int year) {
    return ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0));
}

int main() {
    int y;
    printf("Enter year: ");
    scanf("%d", &y);
    if (isLeapYear(y)) printf("Leap Year\n");
    else printf("Not Leap Year\n");
    return 0;
}

