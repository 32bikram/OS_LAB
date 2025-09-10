/***********************************************************************
*
* Date :
* Team No: 08
*	Partha Roy 	- 	Roll- 302411001004
*	Bikram Sarkar	-	Roll- 302411001008
*	Bikram Dutta	-	Roll- 002311001071 
* 
* What the program does -
*	This program performs parallel multiplication of two large square matrices using Pthreads, dynamically allocating memory and 
*	initializing elements with random values modulo a specified number. It measures and reports the execution time of the multiplication 
*	while supporting configurable thread count and optional matrix output.
*
* Input Description:
*    - The program takes four command-line arguments:
*      1. Matrix Dimension (N) - The size of the square matrices (at least 3000 x 3000).
*      2. Number of Threads (T) - The number of threads to be used for parallel computation.
*      3. Modulus Value (M) - The value used to generate random numbers for the matrices.
*      4. Print Switch (P) - A flag (1 or 0) to control whether the matrices should be printed (1 to print, 0 to skip).
*
* Output Description:
*    - The program performs matrix multiplication between two randomly initialized matrices (A and B).
*    - The resulting matrix (C) is printed if the print switch (P) is set to 1.
*    - The time taken for the matrix multiplication is displayed.
*
* Compilation Command:
*    gcc -o A2_08_6 A2_08_6.c -lpthread
*
* Execution Command:
*    ./A2_08_6 <matrix_size> <num_threads> <mod_value> <print_switch>
*      Example: ./A2_08_6 3000 4 100 1
*        - This will multiply two 3000x3000 matrices using 4 threads, initialize them with random values modulo 100, and print the matrices.
*
* Sample Input:
*    ./A2_08_6 3000 4 300 0
*
* Sample Output:
*    Time taken: 19.920052 seconds
*
* Sample Input:
*    ./A2_08_6 3000 8 300 0
*
* Sample Output:
*    Time taken: 15.907955 seconds
*
*
* Sample Input:
*    ./A2_08_6 3000 12 300 0
*
* Sample Output:
*    Time taken: 14.812807 seconds
*
* Sample Input:
*	./A2_08_6 3 4 20 1
* Sample Output:
*	Time taken: 0.000738 seconds
*	Matrix A:
*	3 17 13
*	6 9 2
*	10 3 0
*	Matrix B:
*	6 15 15
*	12 1 7
*	19 6 6
*	Result Matrix C:
*	213 140 242
*	182 111 165
*	96 153 171
* Output of 'sar' command-
*	sar 1
*	Linux 5.15.0-139-generic (adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC) 10/09/25 _x86_64_ (12 CPU)

*	01:02:45 PM IST     CPU     %user     %nice   %system   %iowait    %steal     %idle
*	01:02:46 PM IST     all      0.50      0.00      0.42      0.17      0.00     98.92
*	01:02:47 PM IST     all      0.34      0.00      0.34      0.00      0.00     99.33
*	01:02:48 PM IST     all      0.33      0.00      0.25      0.00      0.00     99.42
*	01:02:49 PM IST     all     59.57      0.00      0.17      0.00      0.00     40.27
*	01:02:50 PM IST     all    100.00      0.00      0.00      0.00      0.00      0.00
*	01:02:51 PM IST     all     99.92      0.00      0.08      0.00      0.00      0.00
*	01:02:52 PM IST     all     99.92      0.00      0.08      0.00      0.00      0.00
*	01:02:53 PM IST     all     99.92      0.00      0.08      0.00      0.00      0.00
*	01:02:54 PM IST     all     99.67      0.00      0.33      0.00      0.00      0.00
*	01:02:55 PM IST     all     99.92      0.00      0.08      0.00      0.00      0.00
*
* System Command Used-
*	'sar'- used to monitor and record CPU utilization over time, helping analyze system performance during program execution.
*
***********************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define MAX_THREADS 64

// Global matrices
unsigned char **A, **B, **C;
int matrix_size, num_threads, mod_value, print_switch;

// Struct to pass data to threads
typedef struct {
    int row_start;
    int row_end;
} ThreadData;

// Function to multiply matrices
void* multiply(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int i, j, k;
    for (i = data->row_start; i < data->row_end; i++) {
        for (j = 0; j < matrix_size; j++) {
            C[i][j] = 0;
            for (k = 0; k < matrix_size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

// Function to initialize matrices with random values
void initialize_matrices() {
    int i, j;
    A = (unsigned char**)malloc(matrix_size * sizeof(unsigned char*));
    B = (unsigned char**)malloc(matrix_size * sizeof(unsigned char*));
    C = (unsigned char**)malloc(matrix_size * sizeof(unsigned char*));

    for (i = 0; i < matrix_size; i++) {
        A[i] = (unsigned char*)malloc(matrix_size * sizeof(unsigned char));
        B[i] = (unsigned char*)malloc(matrix_size * sizeof(unsigned char));
        C[i] = (unsigned char*)malloc(matrix_size * sizeof(unsigned char));
    }

    // Initialize A and B with random values
    for (i = 0; i < matrix_size; i++) {
        for (j = 0; j < matrix_size; j++) {
            A[i][j] = rand() % mod_value;
            B[i][j] = rand() % mod_value;
        }
    }
}

// Function to print a matrix
void print_matrix(unsigned char **matrix) {
    int i, j;
    for (i = 0; i < matrix_size; i++) {
        for (j = 0; j < matrix_size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Main function
int main(int argc, char *argv[]) {
    struct timeval start, end;
    int i;
    pthread_t threads[MAX_THREADS];
    ThreadData thread_data[MAX_THREADS];

    if (argc != 5) {
        printf("Usage: %s <matrix_size> <num_threads> <mod_value> <print_switch>\n", argv[0]);
        return -1;
    }

    matrix_size = atoi(argv[1]);
    num_threads = atoi(argv[2]);
    mod_value = atoi(argv[3]);
    print_switch = atoi(argv[4]);

    if (num_threads > MAX_THREADS) {
        num_threads = MAX_THREADS;
    }

    // Initialize matrices
    initialize_matrices();

    // Get the starting time
    gettimeofday(&start, NULL);

    // Divide work among threads
    int rows_per_thread = matrix_size / num_threads;
    for (i = 0; i < num_threads; i++) {
        thread_data[i].row_start = i * rows_per_thread;
        thread_data[i].row_end = (i == num_threads - 1) ? matrix_size : (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, multiply, (void *)&thread_data[i]);
    }

    // Join threads
    for (i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Get the ending time
    gettimeofday(&end, NULL);

    // Calculate and print elapsed time
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    printf("Time taken: %.6f seconds\n", time_taken);

    // Print matrices if required
    if (print_switch == 1) {
        printf("Matrix A:\n");
        print_matrix(A);
        printf("Matrix B:\n");
        print_matrix(B);
        printf("Result Matrix C:\n");
        print_matrix(C);
    }

    // Clean up
    for (i = 0; i < matrix_size; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
