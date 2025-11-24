#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include "api.h"
#include "inner.h"

#include "falcon_counters.h"

// op_counter_lib g_counters;

static double get_time_ms(void) {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

void print_counters(void) {
    printf("===== Falcon Math Operation Counters =====\n");
    printf("FFT calls      : %llu\n", (unsigned long long)g_counters.fft_calls);
    printf("iFFT calls     : %llu\n", (unsigned long long)g_counters.ifft_calls);
    // printf("NNT calls      : %llu\n", (unsigned long long)g_counters.nnt_calls);
    printf("Poly mult      : %llu\n", (unsigned long long)g_counters.poly_mult);
    printf("Poly add       : %llu\n", (unsigned long long)g_counters.poly_add);
    printf("Poly sub       : %llu\n", (unsigned long long)g_counters.poly_sub);
}

int main(int argc, char **argv){
    unsigned char pk[CRYPTO_PUBLICKEYBYTES];
    unsigned char sk[CRYPTO_SECRETKEYBYTES];

    unsigned char msg[100];
    unsigned char msg_out[100];
    
    // Test message //
    const char *test_msg = "This is a test message for Falcon-1024.";
    size_t test_msg_len = strlen(test_msg);
    memcpy(msg, test_msg, test_msg_len);

    double task_start, task_end;
    // double it_start, it_end;

    const int KEYGEN_ITERATIONS = 10;
    const int SIGN_ITERATIONS = 100;
    const int VERIFY_ITERATIONS = 100;
    
    //*** Key Gen Benchmark ***//
    printf("\n **** Key Generation Benchmark **** \n");

    int i;
    int ret_err;
    double it_start[KEYGEN_ITERATIONS];
    double it_end[KEYGEN_ITERATIONS];

    // Counters reset
    task_start = get_time_ms();

    for (i = 0; i < KEYGEN_ITERATIONS; i++) {
        it_start[i] = get_time_ms();
        
        ret_err = crypto_sign_keypair(pk, sk);
        
        it_end[i] = get_time_ms();
        
        if (ret_err != 0) {
            fprintf(stderr, "crypto_sign_keypair failed at iteration: %d\n", i);
            return EXIT_FAILURE;
        } 
    };

    task_end = get_time_ms();

    // Find max, min, and avg iteration timings;
    double min_it_time = 9999;
    double max_it_time = 0;
    double sum_it_time = 0;
    double avg_it_time;

    for (i = 0; i < KEYGEN_ITERATIONS; i++) {
        double temp_diff = it_end[i] - it_start[i];
        if (temp_diff > max_it_time) {
            max_it_time = temp_diff;
        }    
        if (temp_diff < min_it_time) {
            min_it_time = temp_diff;
        }
        sum_it_time = sum_it_time + temp_diff;
    }

    avg_it_time = sum_it_time / (double)KEYGEN_ITERATIONS;

    // Find task time
    double task_time = task_end - task_start; 

    printf("Key generation: %d runs \n", KEYGEN_ITERATIONS);
    printf("Benchmark time: %.6f s\n", task_time);
    printf("Avg iteration time: %.6f s\n", avg_it_time);
    printf("Longest iteration: %.6f s\n", max_it_time);
    printf("Shortest iteration: %.6f s\n", min_it_time); 
    print_counters();  

    // //**** Verification Benchmark ****//
    // printf("\n **** Key Generation Benchmark **** \n");
    // it_start[VERIFY_ITERATIONS];
    // it_end[VERIFY_ITERATIONS];


}