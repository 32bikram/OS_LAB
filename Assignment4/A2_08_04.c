/**********************************************************************************************************************
DATE: 22-08-2025
Assignment-4
Group:A2
Team:08

Name: Partha Roy ,      Roll-302411001004 
Name: Bikram Sarkar ,   Roll-302411001008
Name: Bikram Dutta,     Roll-002311001071

* What this Program Does-
    This program creates a large 8 GB file, maps it into memory using mmap(), and repeatedly writes a random byte
    at a random offset, then verifies the write by reading it back.
    While running, it generates page faults that can be observed in another terminal using 'sar -B 1'.


* Compilation Command-
    gcc A2_08_04.c -o A2_08_04

* System Activity Reporting Command (In a separate terminal)-
    sar -B 1
    
* Execution Command-
    ./A2_08_04


* Output-

    * Code Output-
        Success! Offset: 0x11c4ede99, Written byte: 0x38, Verified byte: 0x38
        Success! Offset: 0x296ff958, Written byte: 0x11, Verified byte: 0x11
        Success! Offset: 0x133d6465a, Written byte: 0xd0, Verified byte: 0xd0
        Success! Offset: 0x6911ec42, Written byte: 0x4e, Verified byte: 0x4e
        Success! Offset: 0x6cbaac6e, Written byte: 0x86, Verified byte: 0x86
        Success! Offset: 0x2ff2eeab, Written byte: 0x65, Verified byte: 0x65
        Success! Offset: 0x6942c58d, Written byte: 0xd4, Verified byte: 0xd4


    * System Command(sar) Output-
        Linux 5.15.167.4-microsoft-standard-WSL2 (ass)  08/22/25        _x86_64_        (8 CPU)

        15:06:28     pgpgin/s pgpgout/s   fault/s  majflt/s  pgfree/s pgscank/s pgscand/s pgsteal/s    %vmeff
        15:06:29         0.00    240.00   1540.00      0.00   1688.00      0.00      0.00      0.00      0.00
        15:06:30         0.00     12.00     20.00      0.00      2.00      0.00      0.00      0.00      0.00
        15:06:31         0.00      0.00   1544.00      0.00   1659.00      0.00      0.00      0.00      0.00
        15:06:32         0.00   1536.00    576.00     76.00    217.00      0.00      0.00      0.00      0.00
        15:06:33         0.00   3936.00   2029.00    193.00   1847.00      0.00      0.00      0.00      0.00
        15:06:34         0.00   5316.00    545.00    261.00   3089.00      0.00      0.00      0.00      0.00
        15:06:35         0.00   5528.00   2009.00    272.00   1863.00      0.00      0.00      0.00      0.00
        15:06:36         0.00   5388.00    551.00    263.00    166.00      0.00      0.00      0.00      0.00
        15:06:37         0.00   5408.00   1993.00    263.00   1746.00      0.00      0.00      0.00      0.00

        
* System Command Used-
        'sar' - It collects, reports, and saves system activity information (CPU, memory, I/O, paging, etc.).
        'fallocate' -	Quickly allocates a large empty file on disk without writing zeros.
        'mmap()' - Maps the file into virtual memory for direct memory-like access.
        'msync()'	- Flushes modified memory-mapped pages to disk.
        'munmap()' - Unmaps the file from memory and releases address space.

* Sparse File Name-
        A2_08_04.bin

***************************************************************************************************************/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

#define FILE_NAME "A2_08_04.bin"
#define FILE_SIZE ((off_t)8L * 1024 * 1024 * 1024) // 8 GB

int main() {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "fallocate -l %ld %s", (long)FILE_SIZE, FILE_NAME);
    if (system(cmd) != 0) {
        fprintf(stderr, "Failed to create file\n");
        return 1;
    }

    int fd = open(FILE_NAME, O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    unsigned char *map = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    size_t page_size = sysconf(_SC_PAGE_SIZE);
    if (page_size == -1) {
        perror("sysconf");
        munmap(map, FILE_SIZE);
        close(fd);
        return 1;
    }

    srand((unsigned)time(NULL));

    while (1) {
        off_t F = (off_t)(((uint64_t)rand() << 32 | rand()) % FILE_SIZE);
        unsigned char X = (unsigned char)(rand() % 256);

        // Writing to MMAP
        map[F] = X;

        off_t page_start = F - (F % page_size);

        if (msync(map + page_start, page_size, MS_SYNC) == -1) {
            perror("msync");
            munmap(map, FILE_SIZE);
            close(fd);
            return 1;
        }
        //check if X and X' is same
        unsigned char X_prime = map[F];
        if (X != X_prime) {
            fprintf(stderr, "ERROR at offset 0x%lx: wrote 0x%02x but read 0x%02x\n",
                    (unsigned long)F, X, X_prime);
            munmap(map, FILE_SIZE);
            close(fd);
            return 1;
        }

        printf("Success! Offset: 0x%lx, Written byte: 0x%02x, Verified byte: 0x%02x\n",
               (unsigned long)F, X, X_prime);
        fflush(stdout);
    }

    //unmapping the memory
    munmap(map, FILE_SIZE);
    close(fd);
    return 0;
}
