#include <stdio.h>
#include <math.h>

#define NUM_SECTIONS 1
#define N 100
#define PI 3.14159265358979323846

// High-Pass IIR Filter Coefficients (2nd-order Butterworth Example)
float b[NUM_SECTIONS][3] = { {0.914969, -1.829938, 0.914969} };
float a[NUM_SECTIONS][3] = { {1.0, -1.822694, 0.837182} };

float x[N], y[N];
float XR[N], XI[N], m1[N], m2[N];
float w[NUM_SECTIONS][2] = {0};  // Internal filter memory

int main(void) {
    int i, j;

    // Generate input: sum of two sine waves (low + high frequency)
    for (i = 0; i < N; i++) {
        x[i] = sin(2 * PI * 2 * i / N) + sin(2 * PI * 30 * i / N);
    }

    // DFT of input signal (for magnitude spectrum)
    for (j = 0; j < N; j++) {
        XR[j] = 0; XI[j] = 0;
        for (i = 0; i < N; i++) {
            XR[j] += x[i] * cos(2 * PI * i * j / N);
            XI[j] -= x[i] * sin(2 * PI * i * j / N);
        }
        m1[j] = sqrt(XR[j]*XR[j] + XI[j]*XI[j]) / N;
    }

    // Apply High-Pass IIR Filter
    for (i = 0; i < N; i++) {
        float input = x[i], wn, yn;

        for (int section = 0; section < NUM_SECTIONS; section++) {
            wn = input - a[section][1]*w[section][0] - a[section][2]*w[section][1];
            yn = b[section][0]*wn + b[section][1]*w[section][0] + b[section][2]*w[section][1];

            w[section][1] = w[section][0];
            w[section][0] = wn;
            input = yn;
        }
        y[i] = input;
    }

    // DFT of filtered output
    for (j = 0; j < N; j++) {
        XR[j] = 0; XI[j] = 0;
        for (i = 0; i < N; i++) {
            XR[j] += y[i] * cos(2 * PI * i * j / N);
            XI[j] -= y[i] * sin(2 * PI * i * j / N);
        }
        m2[j] = sqrt(XR[j]*XR[j] + XI[j]*XI[j]) / N;
    }

    // Display first few output samples
    printf("\nHigh-Pass IIR Filter Output (first 10 samples):\n");
    for (i = 0; i < 10; i++)
        printf("y[%d] = %.6f\n", i, y[i]);

    return 0;
}
