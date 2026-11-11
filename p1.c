#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int a[], int l, int m, int r) {
    int *t = malloc((r - l + 1) * sizeof(int)), i = l, j = m + 1, k = 0;
    while (i <= m && j <= r) t[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
    while (i <= m) t[k++] = a[i++];
    while (j <= r) t[k++] = a[j++];
    for (k = 0; k <= r - l; k++) a[l + k] = t[k];
    free(t);
}

void seqSort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        seqSort(a, l, m);
        seqSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

void parSort(int a[], int l, int r) {
    if (r - l < 1000) { seqSort(a, l, r); return; }
    int m = (l + r) / 2;
    #pragma omp parallel sections
    {
        #pragma omp section
        parSort(a, l, m);
        #pragma omp section
        parSort(a, m + 1, r);
    }
    merge(a, l, m, r);
}

int main() {
    int n = 100000;
    int *a = malloc(n * sizeof(int)), *b = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) a[i] = b[i] = rand() % 100000;

    printf("Sorting %d elements...\n\n", n);
    double t = omp_get_wtime();
    seqSort(a, 0, n - 1);
    double ts = omp_get_wtime() - t;

    t = omp_get_wtime();
    parSort(b, 0, n - 1);
    double tp = omp_get_wtime() - t;

    printf("Sequential Merge Sort Time: %f seconds\n", ts);
    printf("Parallel Merge Sort Time:   %f seconds\n\n", tp);
    printf("Difference (Sequential - Parallel): %f seconds\n", ts - tp);
    printf("Speedup: %.2fx\n\n", ts / tp);
    printf("Verification: First 20 elements of the sorted array:\n");
    for (int i = 0; i < 20; i++) printf("%d ", b[i]);
    printf("\n");
    free(a); free(b);
    return 0;
}