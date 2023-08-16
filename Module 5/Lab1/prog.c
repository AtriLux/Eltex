#include <stdio.h>
#include <stdlib.h>

extern double power2(double num);
extern double sqrt2(double num);

int main(int argc, char* argv[]) {
    double num = atof(argv[1]);
    printf("power2(%0.3f) = ", num);
    printf("%0.3f\n", power2(num));
    printf("sqrt2(%0.3f) = ", num);
    printf("%0.3f\n", sqrt2(num));
    return 0;
}