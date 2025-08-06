/*
==================================================================================
Program     : FIFO Double File Transfer using fork()
Author      : Bikram Sarkar
Date        : 2025-08-06
Description : 
    - Creates a 1GB file
    - Uses fork() to create child
    - Parent writes file to child through FIFO1
    - Child sends it back through FIFO2
    - Final file is compared with the original
    - Time taken for transfer is printed

Commands used (outputs shown below):
------------------------------------
1. File creation:
    dd if=/dev/urandom of=original_file bs=1M count=1024

2. FIFO creation:
    mkfifo fifo1
    mkfifo fifo2

3. File comparison:
    cmp original_file received_file

4. ls -l:
    -rw-r--r-- 1 user user 1073741824 Aug  6 14:00 original_file
    prw-r--r-- 1 user user         0 Aug  6 14:00 fifo1
    prw-r--r-- 1 user user         0 Aug  6 14:00 fifo2
    -rw-r--r-- 1 user user 1073741824 Aug  6 14:00 received_file

5. Time taken:
    Time taken for round-trip transfer: X.XXX seconds
==================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define FILE1 "original_file"
#define FILE2 "received_file"
#define BUFFER_SIZE 4096

/*this fuction is used for the purpose of wrapping error massege using perror()
it exits the program if anything fails*/
void error_exit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);1073741824 Augues if the fifo files already exists
    if (mkfifo(FIFO1, 0666) == -1 && errno != EEXIST)
        error_exit("mkfifo fifo1");

    if (mkfifo(FIFO2, 0666) == -1 && errno != EEXIST)
        error_exit("mkfifo fifo2");

    /* Create 1GB file using dd command. This could be done in the terminal for the file to be used in code. If a file with that same name already exists it 'dd' will overwrite it without any warning*/
    system("dd if=/dev/urandom of=original_file bs=1M count=1024 status=none");
    
    //pid_t is a data type that is used to store process IDs
    pid_t pid;
    char buffer[BUFFER_SIZE];
    
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    //fork() is used to create a child process
    pid = fork();
    if (pid < 0) {
        error_exit("fork");
    }
    else if (pid == 0) {
        // this is Child Process
        int readfd = open(FIFO1, O_RDONLY); // wait for Parent to write in Readonly mode
        int tempfd = open("temp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644); //tempfd temporarily hold onto the data received from FIFO01

        if (readfd == -1 || tempfd == -1)
            error_exit("child: open fifo1/temp_file");

        ssize_t bytes;
        //Reads data from the FIFO01 in chunks and writes to temp_file.
        while ((bytes = read(readfd, buffer, BUFFER_SIZE)) > 0) {
            write(tempfd, buffer, bytes);
        }

        close(readfd);
        close(tempfd);

        // Send back to parent using fifo2
        int writefd = open(FIFO2, O_WRONLY);
        tempfd = open("temp_file", O_RDONLY);

        if (writefd == -1 || tempfd == -1)
            error_exit("child: open fifo2/temp_file");

        while ((bytes = read(tempfd, buffer, BUFFER_SIZE)) > 0) {
            write(writefd, buffer, bytes);
        }

        close(writefd);
        close(tempfd);

        unlink("temp_file"); // temporary file is deleted
    }
    else {
        // Parent Process
        int writefd = open(FIFO1, O_WRONLY);
        int filefd = open(FILE1, O_RDONLY);

        if (writefd == -1 || filefd == -1)
            error_exit("parent: open fifo1/file1");

        ssize_t bytes;
        while ((bytes = read(filefd, buffer, BUFFER_SIZE)) > 0) {
            write(writefd, buffer, bytes);
        }

        close(writefd);
        close(filefd);

        // Read back from child via fifo2
        int readfd = open(FIFO2, O_RDONLY);
        int outfd = open(FILE2, O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if (readfd == -1 || outfd == -1)
            error_exit("parent: open fifo2/file2");

        while ((bytes = read(readfd, buffer, BUFFER_SIZE)) > 0) {
            write(outfd, buffer, bytes);
        }

        close(readfd);
        close(outfd);

        wait(NULL); // Wait for child

        // End time
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_taken = (end.tv_sec - start.tv_sec) + 
                            (end.tv_nsec - start.tv_nsec) / 1e9;

        // Compare the two files
        int cmp_result = system("cmp original_file received_file");

        if (cmp_result == 0) {
            printf("✅ Files match. Transfer successful.\n");
        } else {
            printf("❌ Files do NOT match.\n");
        }

        printf("⏱️ Time taken for round-trip transfer: %.3f seconds\n", time_taken);
    }

    // Cleanup of the FIFO
    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}
