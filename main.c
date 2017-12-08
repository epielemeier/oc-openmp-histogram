#include <stdio.h>
#include <stdlib.h>
#ifndef _OMP_H
#   include "omp.h"
#endif
#include "histogram.h"
#define DATA_COUNT 20

float find_max(int data_count, float *data);
float find_min(int data_count, float *data);

int main() {
    int bin_count = 5;
    float data[DATA_COUNT] = {1.3, 2.9, 0.4, 0.3, 1.3, 4.4, 1.7, 0.4, 3.2, 0.3, 4.9, 2.4, 3.1, 4.4, 3.9, 0.4, 4.2, 4.5, 4.9, 0.9};
    float max = find_max(DATA_COUNT, data);
    float min = find_min(DATA_COUNT, data);

    double start_time = omp_get_wtime();
    struct histogram_type h = compute_histogram(DATA_COUNT, data, min, max, bin_count);
    double end_time = omp_get_wtime();

    char *str = histogram_to_string(h);
    printf("Histogram:\n%s\n", str);
    printf("Performance: %f\n", end_time - start_time);

    free(str);
    free_histogram(&h);

    return 0;
}

float find_max(int data_count, float *data) {
    float value = (data_count > 0) ? data[0] : 0;
#pragma omp parallel for reduction(max: value)
    for (int i = 0; i < data_count; i++) {
        if (data[i] > value)
            value = data[i];
    }
    return value;
}

float find_min(int data_count, float *data) {
    float value = (data_count > 0) ? data[0] : 0;
#pragma omp parallel for reduction(min: value)
    for (int i = 0; i < data_count; i++) {
        if (data[i] < value)
            value = data[i];
    }
    return value;
}
