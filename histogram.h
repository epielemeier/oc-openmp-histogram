#ifndef OPENMP_PROBLEM_1_HISTOGRAM_H
#define OPENMP_PROBLEM_1_HISTOGRAM_H

struct histogram_type {
    float *bin_maxes;
    int *bin_counts;
    int num_bins;
} histogram_type;

struct histogram_type malloc_histogram(int num_bins);
void free_histogram(struct histogram_type*);
char* histogram_to_string(struct histogram_type);
struct histogram_type compute_histogram(int data_count, float *data, float min_meas, float max_meas, int bin_count);
#endif