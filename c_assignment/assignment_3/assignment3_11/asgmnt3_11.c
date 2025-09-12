#include <stdio.h>

int isLeapYear(int y) {
    return ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0));
}

int isValidDate(int d, int m, int y) {
    if (y < 1 || m < 1 || m > 12 || d < 1) return 0;
    int days;
    if (m == 2) days = isLeapYear(y) ? 29 : 28;
    else if (m == 4 || m == 6 || m == 9 || m == 11) days = 30;
    else days = 31;
    return d <= days;
}

int main() {
    int d, m, y;
    printf("Enter date (dd mm yyyy): ");
    scanf("%d %d %d", &d, &m, &y);
    if (isValidDate(d, m, y)) printf("Valid Date\n");
    else printf("Invalid Date\n");
    return 0;
}

