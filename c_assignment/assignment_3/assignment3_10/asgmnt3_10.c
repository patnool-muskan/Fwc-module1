#include <stdio.h>

int isLeapYear(int y) {
    return ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0));
}

int daysInMonth(int m, int y) {
    if (m == 2) return isLeapYear(y) ? 29 : 28;
    if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
    return 31;
}

int main() {
    int m, y;
    printf("Enter month and year: ");
    scanf("%d %d", &m, &y);
    printf("Days = %d\n", daysInMonth(m, y));
    return 0;
}

