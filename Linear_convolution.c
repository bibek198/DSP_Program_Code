#include <stdio.h>
#include <math.h>

#define MAX 50  // maximum allowed sequence length

int main() {
    int i, j;
    int N1, N2, N;
    double x1[MAX], x2[MAX], y[MAX] = {0};

    // ---- Step 1: Input Sequences ----
    printf("Enter length of first sequence (x1): ");
    scanf("%d", &N1);
    printf("Enter %d elements of x1:\n", N1);
    for (i = 0; i < N1; i++)
        scanf("%lf", &x1[i]);

    printf("Enter length of second sequence (x2): ");
    scanf("%d", &N2);
    printf("Enter %d elements of x2:\n", N2);
    for (i = 0; i < N2; i++)
        scanf("%lf", &x2[i]);

    // ---- Step 2: Compute length of result ----
    N = N1 + N2 - 1;

    // ---- Step 3: Perform Linear Convolution ----
    for (i = 0; i < N1; i++) {
        for (j = 0; j < N2; j++) {
            y[i + j] += x1[i] * x2[j];
        }
    }

    // ---- Step 4: Display Result ----
    printf("\nLinear Convolution Result (length = %d):\n", N);
    for (i = 0; i < N; i++)
        printf("y[%d] = %.2f\n", i, y[i]);

    return 0;
}
