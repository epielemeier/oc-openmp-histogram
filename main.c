#include <stdio.h>
#ifndef _OMP_H
#   include "omp.h"
#endif
#define DATA_COUNT 20

int main() {
    int bin_count = 5;
    float data[DATA_COUNT] = {1.3, 2.9, 0.4, 0.3, 1.3, 4.4, 1.7, 0.4, 3.2, 0.3, 4.9, 2.4, 3.1, 4.4, 3.9, 0.4, 4.2, 4.5, 4.9, 0.9};
    return 0;
}
