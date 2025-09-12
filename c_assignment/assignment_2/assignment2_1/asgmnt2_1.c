#include <stdio.h>

// Structure for circle results
struct Circle {
    float area;
    float perimeter;
};

// Function to calculate area and perimeter
struct Circle calculateCircle(float radius) {
    struct Circle result;
    result.area = 3.14159f * radius * radius;
    result.perimeter = 2 * 3.14159f * radius;
    return result;
}

int main() {
    float r;
    printf("Enter radius: ");
    scanf("%f", &r);

    struct Circle res = calculateCircle(r);

    printf("Area = %.2f\n", res.area);
    printf("Perimeter = %.2f\n", res.perimeter);

    return 0;
}

