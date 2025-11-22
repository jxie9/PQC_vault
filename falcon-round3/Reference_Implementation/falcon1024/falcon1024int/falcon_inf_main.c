#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "api.h"
#include "inner.h"

#include "falcon_counters.h"

op_counter_lib g_counters;

int main(int argc, char **argv){
    unsigned char pk[CRYPTO_PUBLICKEYBYTES];
    unsigned char sk[CRYPTO_SECRETKEYBYTES];

    unsigned char msg[100];
    unsigned char msg_out[100];
    
    // Test message //
    const char *test_msg = "This is a test message for Falcon-1024.";
    size_t test_msg_len = strlen(test_msg);
    memcpy(msg, test_msg, test_msg_len);

    double t_start, t_end;

    const int KEYGEN_ITERATIONS = 10;
    const int SIGN_ITERATIONS = 100;
    const int VERIFY_ITERATIONS = 100;
    
    //*** Key Gen Benchmark ***//
    printf("\n **** Key Generation Benchmark **** \n");
    // Counters reset
    // Start benchmark timer
    int i;
    int ret_err;
    int min_it_time = 0;
    int max_it_time = 9999;
    for (i = 0; i < KEYGEN_ITERATIONS; i++) {
        // Start iteration timer
        ret_err = crypto_sign_keypair(pk, sk);
        // End iteration timer
        // Update min, max times
        if (ret_err != 0) {
            fprintf(stderr, "crypto_sign_keypair failed at iteration: %d\n", i);
            return EXIT_FAILURE;
        } 
    };
    // Stop benchmark timer

    printf("Key generation: %d runs \n", KEYGEN_ITERATIONS);
    //printf("Benchmark time: %.6f s\n", );
    printf("Avg iteration time: ");
    printf("Longest iteration: ");
    printf("Shortest iteration: ");

}