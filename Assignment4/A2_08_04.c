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

#define FILE_NAME "bigfile.bin"
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

        // Write directly to mmap
        map[F] = X;

        // Calculate page aligned address and length for msync
        off_t page_start = F - (F % page_size);

        // Sync one full page
        if (msync(map + page_start, page_size, MS_SYNC) == -1) {
            perror("msync");
            munmap(map, FILE_SIZE);
            close(fd);
            return 1;
        }

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

    munmap(map, FILE_SIZE);
    close(fd);
    return 0;
}
