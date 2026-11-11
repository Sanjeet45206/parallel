#include <stdio.h>
#include <omp.h>

int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

int main() {
    int n, cs = 0, cp = 0;
    printf("Enter the upper limit (n) to find prime numbers: ");
    scanf("%d", &n);
    printf("\nFinding prime numbers from 1 to %d...\n", n);

    double t = omp_get_wtime();
    for (int i = 1; i <= n; i++) cs += isPrime(i);
    double ts = omp_get_wtime() - t;
    printf("\nSequential: Found %d primes in %f seconds\n", cs, ts);

    t = omp_get_wtime();
    #pragma omp parallel for reduction(+:cp) schedule(dynamic)
    for (int i = 1; i <= n; i++) cp += isPrime(i);
    double tp = omp_get_wtime() - t;
    printf("Parallel:   Found %d primes in %f seconds\n", cp, tp);

    printf("\nSpeedup: %.2fx\n", ts / tp);
    return 0;
}