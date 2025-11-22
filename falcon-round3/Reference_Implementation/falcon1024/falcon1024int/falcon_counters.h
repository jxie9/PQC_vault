#ifndef FALCON_COUNTERS_H
#define FALCON_COUNTERS_H

#include <stdint.h>

typedef struct {
    uint64_t fft_calls;
    uint64_t ifft_calls;
    uint64_t nnt_calls;
    uint64_t poly_mult;
} op_counter_lib;

extern op_counter_lib g_counters;

// Reset all counters 
static inline void reset_counters(void) {
    g_counters.fft_calls = 0;
    g_counters.ifft_calls = 0;
    g_counters.nnt_calls = 0;
    g_counters.poly_mult = 0;
}

#define FALCON_COUNT_FFT() (g_counters.fft_calls++)
#define FALCON_COUNT_IFFT() (g_counters.ifft_calls++)
#define FALCON_COUNT_NNT() (g_counters.nnt_calls++)
#define FALCON_COUNT_POLYMULT() (g_counters.poly_mult++)

#endif 