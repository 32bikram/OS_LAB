/***************************************************************************************************************************
 
 *   DATE: 05-09-2025
 *   Assignment-5
 *   Group:A2
 *   Team:08
 
 *  Name: Partha Roy ,      Roll-302411001004 
 *  Name: Bikram Sarkar ,   Roll-302411001008
 *  Name: Bikram Dutta,     Roll-002311001071

 *  What the program does-
        The program creates a shared memory segment and spawns three threads to compute values based on random 
        (𝑋,𝑌)(X,Y) pairs.For each pair, it calculates 𝐴=𝑋×𝑌A=X×Y, 𝐵=2𝑋+2𝑌+1B=2X+2Y+1, and 𝐶=𝐵/𝐴C=B/A,
        then stores and displays the results in a synchronized tabular format.

 *  Compilation Command-
        gcc A2_08_05.c -o A2_08_05 -lpthread -lrt

 *  Command To check Shared Memory Status-
        ipcs -m

 *  Execution Command-
        ./A2_08_05 10
 
 *  Output-
       * Code Output-
                Pairs(X,Y) | A | B | C
                --------------------------------------------------
                (0, 9) | 0 | 19 | -
                (7, 1) | 7 | 17 | 2.42857
                (3, 3) | 9 | 13 | 1.44444
                (4, 1) | 4 | 11 | 2.75
                (0, 4) | 0 | 9 | -
                (7, 6) | 42 | 27 | 0.642857
                (0, 4) | 0 | 9 | -
                (4, 6) | 24 | 21 | 0.875
                (0, 1) | 0 | 3 | -
                (3, 1) | 3 | 9 | 3
                --------------------------------------------------
       * System Command(ipcs) Output-
                ------ Shared Memory Segments --------
                key        shmid      owner      perms      bytes      nattch     status
                0x00000000 6          kiertolain 600        2000004    1  

 *  System Command Used-
        'ipcs -m' - it's a Linux command-line tool that shows the status of System V IPC resources like Shared memory (-m).
        'shmget' - shmget is a system call used to create a new shared memory segment or access an existing one.
        'shmctl' - shmctl stands for shared memory control, It perform administrative operations on a shared memory segment.
        'shmdt' - It detaches a shared memory segment from the address space of the calling process.

****************************************************************************************************************************/
#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <errno.h>


static pthread_barrier_t barrier;
static pthread_mutex_t ready_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t ready_cond = PTHREAD_COND_INITIALIZER;


static int *gX = NULL;
static int *gY = NULL;
static double *gA = NULL;
static double *gB = NULL;
static double *gC = NULL;
static int *gReadyA = NULL;
static int *gReadyB = NULL;
static int  gN = 0;


void *thread_A(void *arg) {
    (void)arg;
    for (int i = 0; i < gN; ++i) {
       
        pthread_barrier_wait(&barrier);

        
        double A = (double)gX[i] * (double)gY[i];
        gA[i] = A;

        
        pthread_mutex_lock(&ready_lock);
        gReadyA[i] = 1;
        pthread_cond_broadcast(&ready_cond);
        pthread_mutex_unlock(&ready_lock);
    }
    return NULL;
}

void *thread_B(void *arg) {
    (void)arg;
    for (int i = 0; i < gN; ++i) {
        pthread_barrier_wait(&barrier);

        /* compute B = 2*X + 2*Y + 1 */
        double B = 2.0 * (double)gX[i] + 2.0 * (double)gY[i] + 1.0;
        gB[i] = B;

        pthread_mutex_lock(&ready_lock);
        gReadyB[i] = 1;
        pthread_cond_broadcast(&ready_cond);
        pthread_mutex_unlock(&ready_lock);
    }
    return NULL;
}

void *thread_C(void *arg) {
    (void)arg;
    for (int i = 0; i < gN; ++i) {
        pthread_barrier_wait(&barrier);

        // wait until both A and B are ready for index i 
        pthread_mutex_lock(&ready_lock);
        while (!(gReadyA[i] && gReadyB[i])) {
            pthread_cond_wait(&ready_cond, &ready_lock);
        }
        
        double A = gA[i];
        double B = gB[i];
        pthread_mutex_unlock(&ready_lock);

        // compute C = B / A (handle A==0) 
        double C;
        if (A == 0.0) {
            C = NAN; /* undefined */
        } else {
            C = B / A;
        }
        gC[i] = C;
    }
    return NULL;
}


size_t compute_shm_size(int N) {
    
    size_t size = 0;
    size += sizeof(int); 
    size += N * sizeof(int);   
    size += N * sizeof(int);   
    size += N * sizeof(double);
    size += N * sizeof(double);
    size += N * sizeof(double);
    size += N * sizeof(int);     
    size += N * sizeof(int);     
    return size;
}


void map_shm_block(void *blk, int N) {
    char *p = (char *)blk;
    
    memcpy(p, &N, sizeof(int));
    p += sizeof(int);

    gX = (int *)p;
    p += N * sizeof(int);

    gY = (int *)p;
    p += N * sizeof(int);

    gA = (double *)p;
    p += N * sizeof(double);

    gB = (double *)p;
    p += N * sizeof(double);

    gC = (double *)p;
    p += N * sizeof(double);

    gReadyA = (int *)p;
    p += N * sizeof(int);

    gReadyB = (int *)p;
    p += N * sizeof(int);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s N\n  N = number of random pairs (positive integer)\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int N = atoi(argv[1]);
    if (N <= 0) {
        fprintf(stderr, "N must be positive.\n");
        exit(EXIT_FAILURE);
    }
    gN = N;

   
    key_t key = IPC_PRIVATE; 
    size_t shm_size = compute_shm_size(N);
    int shmid = shmget(key, (int)shm_size, IPC_CREAT | 0600);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    
    void *shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (void *)-1) {
        perror("shmat");
        
        shmctl(shmid, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    }

    
    map_shm_block(shmaddr, N);

    
    for (int i = 0; i < N; ++i) {
        gX[i] = 0;
        gY[i] = 0;
        gA[i] = 0.0;
        gB[i] = 0.0;
        gC[i] = NAN;
        gReadyA[i] = 0;
        gReadyB[i] = 0;
    }

   
    srand((unsigned)time(NULL) ^ (unsigned)getpid());
    for (int i = 0; i < N; ++i) {
        gX[i] = rand() % 10; /* 0..9 */
        gY[i] = rand() % 10; /* 0..9 */
    }

    
    if (pthread_barrier_init(&barrier, NULL, 3) != 0) {
        perror("pthread_barrier_init");
        shmdt(shmaddr);
        shmctl(shmid, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    }

    pthread_t thA, thB, thC;
    if (pthread_create(&thA, NULL, thread_A, NULL) != 0) {
        perror("pthread_create A");
        goto cleanup_shm;
    }
    if (pthread_create(&thB, NULL, thread_B, NULL) != 0) {
        perror("pthread_create B");
        goto cleanup_threads;
    }
    if (pthread_create(&thC, NULL, thread_C, NULL) != 0) {
        perror("pthread_create C");
        goto cleanup_threads;
    }

    
    pthread_join(thA, NULL);
    pthread_join(thB, NULL);
    pthread_join(thC, NULL);

    
    printf("Pairs(X,Y) | A | B | C\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < N; ++i) {
        double A = gA[i];
        double B = gB[i];
        double C = gC[i];
        
        if (isnan(C)) {
            printf("(%d, %d) | %.0f | %.0f | -\n", gX[i], gY[i], A, B);
        } else {
            
            printf("(%d, %d) | %.0f | %.0f | %.6g\n", gX[i], gY[i], A, B, C);
        }
    }
    printf("--------------------------------------------------\n");

    
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
    }
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl(IPC_RMID)");
    }

    pthread_barrier_destroy(&barrier);
    pthread_mutex_destroy(&ready_lock);
    pthread_cond_destroy(&ready_cond);

    return 0;


cleanup_threads:
    
    pthread_cancel(thA);
    pthread_cancel(thB);
    pthread_cancel(thC);
    pthread_join(thA, NULL);
    pthread_join(thB, NULL);
    pthread_join(thC, NULL);

cleanup_shm:
    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, NULL);
    exit(EXIT_FAILURE);
}

