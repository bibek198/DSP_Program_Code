#include <stdio.h>
#include <math.h>

#define MAX 50   // maximum allowed sequence length

int main() {
    int i, j, k;
    int N1, N2, N; 
    double x1[MAX], x2[MAX], y[MAX];
    double temp[MAX];

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

    // ---- Step 2: Pad smaller sequence ----
    N = (N1 > N2) ? N1 : N2;
    for (i = N1; i < N; i++) x1[i] = 0;
    for (i = N2; i < N; i++) x2[i] = 0;

    // ---- Step 3: Initialize output ----
    for (i = 0; i < N; i++) y[i] = 0;

    // ---- Step 4: Circular Convolution ----
    for (k = 0; k < N; k++) {
        for (i = 0; i < N; i++) {
            // Wrap-around index using modulo
            int j = (k - i + N) % N;
            y[k] += x1[i] * x2[j];
        }
    }

    // ---- Step 5: Display Result ----
    printf("\nCircular Convolution Result (length = %d):\n", N);
    for (i = 0; i < N; i++)
        printf("y[%d] = %.2f\n", i, y[i]);

    return 0;
}
