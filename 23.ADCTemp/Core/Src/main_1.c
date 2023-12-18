#include <stdio.h>
#include "computer.h"

int main() {
    int a = 5;
    int b = 3;

    int sum_result = sum(a, b);
    int subtract_result = subtract(a, b);
    float radius = 2.5;
    float area = AREA_OF_CIRCLE(radius);

    printf("Sum: %d\n", sum_result);
    printf("Subtraction: %d\n", subtract_result);
    printf("Area of Circle: %f\n", area);

    return 0;
}
