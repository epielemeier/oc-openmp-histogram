#include <stdlib.h>
#include <stdio.h>
#ifndef _OMP_H
#   include "omp.h"
#endif
#include "histogram.h"

struct histogram_type malloc_histogram(int num_bins) {
    struct histogram_type h;
    h.num_bins = num_bins;
    h.bin_maxes = (float *) malloc(num_bins * sizeof(float));
    h.bin_counts = (float *) calloc(num_bins, sizeof(float));
    return h;
}

void free_histogram(struct histogram_type* h) {
    free(h->bin_maxes);
    free(h->bin_counts);
}

char* histogram_to_string(struct histogram_type h) {
    char* str = malloc(30 + 20 * h.num_bins * sizeof(char));
    char* beginning = str;
    sprintf(str, "%15s", "Bin counts:");
    str += 15;
    for (int i = 0; i < h.num_bins; i++) {
        sprintf(str, "%10d\t", h.bin_counts[i]);
        str += 10;
    }
    sprintf(str++, "\n");
    sprintf(str, "%15s", "Bin maxes:");
    str += 15;
    for (int i = 0; i < h.num_bins; i++) {
        sprintf(str, "%10f\t", h.bin_maxes[i]);
        str += 10;
    }
    return beginning;
}

int find_bin_for_datum(float d, struct histogram_type *h) {
    for (int i = 0; i < h->num_bins; i++) {
        if (d <= h->bin_maxes[i] && (i == 0 || d > h->bin_maxes[i - 1])) {
            return i;
        }
    }
}

struct histogram_type compute_histogram(int data_count, float *data, float min_meas, float max_meas, int bin_count) {
    struct histogram_type h = malloc_histogram(bin_count);
    float bin_width = (max_meas - min_meas) / h.num_bins;
    // compute maxes for each bin
#pragma omp parallel for
    for (int i = 0; i < h.num_bins; i++)
        h.bin_maxes[i] = min_meas + bin_width * (i + 1);

    // init locks for each bin
    omp_lock_t *locks = (omp_lock_t *) malloc(sizeof(omp_lock_t*));
#pragma omp parallel for
    for (int i = 0; i < h.num_bins; i++)
        omp_init_lock(&locks[i]);

    // compute counts for each bin
    int bin;
#pragma omp parallel for private(bin)
    for (int i = 0; i < data_count; i++) {
        bin = find_bin_for_datum(data[i], &h);
        omp_set_lock(&locks[bin]);
        h.bin_counts[bin]++;
        omp_unset_lock(&locks[bin]);
    }

    // free locks
#pragma omp parallel for
    for (int i = 0; i < h.num_bins; i++)
        omp_destroy_lock(&locks[i]);

    return h;
}