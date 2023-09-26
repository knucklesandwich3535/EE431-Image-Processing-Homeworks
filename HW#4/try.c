#include "img_pro.h"

#define M 512
#define N 512

// Structure to store complex numbers
typedef struct {
double real;
double imag;
} complex_t;

// Function to perform 2D DFT
void dft2d(double *x, complex_t *X, int m, int n)
{
for (int k = 0; k < m; k++)
{
for (int l = 0; l < n; l++)
{
double sumreal = 0;
double sumimag = 0;
for (int i = 0; i < m; i++)
{
for (int j = 0; j < n; j++)
{
double angle = 2 * M_PI * ((i * k / (double)m) + (j * l / (double)n));
sumreal += x[i * n + j] * cos(angle);
sumimag -= x[i * n + j] * sin(angle);
}
}
X[k * n + l].real = sumreal;
X[k * n + l].imag = sumimag;
}
}
}

// Function to perform 2D inverse DFT
void idft2d(complex_t *X, double *x, int m, int n)
{
for (int i = 0; i < m; i++)
{
for (int j = 0; j < n; j++)
{
double sumreal = 0;
double sumimag = 0;
for (int k = 0; k < m; k++)
{
for (int l = 0; l < n; l++)
{
double angle = 2 * M_PI * ((i * k / (double)m) + (j * l / (double)n));
sumreal += X[k * n + l].real * cos(angle) - X[k * n + l].imag * sin(angle);
sumimag += X[k * n + l].real * sin(angle) + X[k * n + l].imag * cos(angle);
}
}
x[i * n + j] = (sumreal / (m * n)) + (sumimag / (m * n));
}
}
}

int main(int argc, char *argv[])
{
// Read image file
char *infile = argv[1];
FILE *fp = fopen(infile, "rb");
if (!fp)
{
printf("Error opening input file.\n");
return 1;
}
// Read center frequency and bandwidth
int r = atoi(argv[2]);
int bw = atoi(argv[3]);

// Allocate memory for image
double *x = (double*)malloc(M * N * sizeof(double));
complex_t *X = (complex_t*)malloc(M * N * sizeof(complex_t));
if(!x || !X)
{
printf("Error allocating memory.\n");
return 1;
}
// Read image data from file
for (int i = 0; i < M; i++)
{
    for (int j = 0; j < N; j++)
    {
        fread(&x[i * N + j], sizeof(double), 1, fp);
    }
}
fclose(fp);

// Perform 2D DFT
dft2d(x, X, M, N);

// Shift low frequency components to center
for (int i = 0; i < M / 2; i++)
{
    for (int j = 0; j < N / 2; j++)
    {
        complex_t tmp = X[i * N + j];
        X[i * N + j] = X[(i + M / 2) * N + (j + N / 2)];
        X[(i + M / 2) * N + (j + N / 2)] = tmp;
    }
}

// Apply band-pass filter
for (int i = 0; i < M / 2; i++)
{
    for (int j = 0; j < N / 2; j++)
    {
        int d = sqrt((i - r) * (i - r) + (j - r) * (j - r));
        if (d > r - bw / 2 && d < r + bw / 2)
        {
            X[i * N + j].real = 0;
            X[i * N + j].imag = 0;
            X[(i + M / 2) * N + (j + N / 2)].real = 0;
            X[(i + M / 2) * N + (j + N / 2)].imag = 0;
        }
    }
}

// Perform 2D inverse DFT
idft2d(X, x, M,N);

// Write output image to file
char *outfile = "filtered.ppm";
fp = fopen(outfile, "wb");
if (!fp)
{
    printf("Error opening output file.\n");
    return 1;
}
for (int i = 0; i < M; i++)
{
    for (int j = 0; j < N; j++)
    {
        fwrite(&x[i * N + j], sizeof(double), 1, fp);
    }
}
fclose(fp);

show_pgm_file("filtered.ppm"); 

free(x);
free(X);

return 0;
}
