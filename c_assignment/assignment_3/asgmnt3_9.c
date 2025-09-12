#include <stdio.h>

// Function to compare two dates
int IsFirstDateOlder(int d1, int m1, int y1, int d2, int m2, int y2) {
    // Compare year
    if (y1 < y2) return 1;
    else if (y1 > y2) return 0;

    // If years are equal, compare month
    if (m1 < m2) return 1;
    else if (m1 > m2) return 0;

    // If months are also equal, compare day
    if (d1 < d2) return 1;
    else return 0;  // either same day or second is older
}

int main() {
    int d1, m1, y1;
    int d2, m2, y2;

    printf("Enter first date (dd mm yyyy): ");
    scanf("%d %d %d", &d1, &m1, &y1);

    printf("Enter second date (dd mm yyyy): ");
    scanf("%d %d %d", &d2, &m2, &y2);

    if (IsFirstDateOlder(d1, m1, y1, d2, m2, y2))
        printf("The first date is older.\n");
    else
        printf("The second date is older.\n");

    return 0;
}

