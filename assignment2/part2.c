/********************************************************************
*   Group:A2
*   Team:08
*   Date: 07-08-2025
*   Assignment-2B
*
*   Name: Partha Roy ,      Roll-302411001004 
*   Name: Bikram Sarkar ,   Roll-302411001008
*   Name: Bikram Dutta,     Roll-002311001071
*
*Compilation Command-
*   gcc A2_08_2B.c -o A2_08_2B
*
*Execution Command-
*   ./A2_08_2B
*
*HostName-
*   kiertolainen
* 
*Sample Output:-
*   Successfull Execution-
*       prw-r--r-- 1 kiertolainen kiertolainen          0 Aug  7 14:11 fifo1
*       prw-r--r-- 1 kiertolainen kiertolainen          0 Aug  7 14:11 fifo2
*       -rw-r--r-- 1 kiertolainen kiertolainen 1073741824 Aug  7 14:11 original_file
*       -rw-r--r-- 1 kiertolainen kiertolainen        511 Aug  7 13:29 part1.c
*       -rw-r--r-- 1 kiertolainen kiertolainen 1073741824 Aug  7 14:11 received_file
*       Files match. Transfer successful.
*       Time taken for round-trip transfer: xx seconds
*
*   Unsucssefull Execution-
*       Files do NOT match.
*
*Actual Output-
*    total 2097208
*    -rwxr-xr-x 1 kiertolainen kiertolainen      16656 Aug  7 14:11 A2_08_2B
*    -rw-r--r-- 1 kiertolainen kiertolainen       4078 Aug  7 14:11 A2_08_2B.c
*    -rwxr-xr-x 1 kiertolainen kiertolainen      16656 Aug  7 13:54 a.out
*    prw-r--r-- 1 kiertolainen kiertolainen          0 Aug  7 14:11 fifo1
*    prw-r--r-- 1 kiertolainen kiertolainen          0 Aug  7 14:11 fifo2
*    -rw-r--r-- 1 kiertolainen kiertolainen 1073741824 Aug  7 14:11 original_file
*    -rw-r--r-- 1 kiertolainen kiertolainen        511 Aug  7 13:29 part1.c
*    -rw-r--r-- 1 kiertolainen kiertolainen 1073741824 Aug  7 14:11 received_file
*    Files match. Transfer successful.
*    Time taken for round-trip transfer: 4.816 seconds
*    total 2097208
*    -rwxr-xr-x 1 kiertolainen kiertolainen      16656 Aug  7 14:11 A2_08_2B
*    -rw-r--r-- 1 kiertolainen kiertolainen       4078 Aug  7 14:11 A2_08_2B.c
*    -rwxr-xr-x 1 kiertolainen kiertolainen      16656 Aug  7 13:54 a.out
*    -rw-r--r-- 1 kiertolainen kiertolainen 1073741824 Aug  7 14:11 original_file
*    -rw-r--r-- 1 kiertolainen kiertolainen        511 Aug  7 13:29 part1.c
*    -rw-r--r-- 1 kiertolainen kiertolainen 1073741824 Aug  7 14:11 received_file
*
*System Command Used-
*   'dd' to create a 1GB demo file.
*   'mkfifo' is used to create the fifos.
*   'ls -l' is used to show the file and fifo details.
*   'cmp' is used to compare the original file and the recived file.
*FIFO names-
*   Parent fifo- fifo1
*   Child fifo- fifo2
*File Names-
*   Sended file- original_file
*   Received file- received_file
*********************************************************************/
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

// Error handler: prints message and exits
void error_exit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    // Create FIFO files (if not already exist)
    if (mkfifo(FIFO1, 0666) == -1 && errno != EEXIST)
        error_exit("mkfifo fifo1");

    if (mkfifo(FIFO2, 0666) == -1 && errno != EEXIST)
        error_exit("mkfifo fifo2");

    // Create 1GB random file using dd
    system("dd if=/dev/urandom of=original_file bs=1M count=1024 status=none");

    pid_t pid;
    char buffer[BUFFER_SIZE];
    struct timespec start, end;
    //starting the timer
    clock_gettime(CLOCK_MONOTONIC, &start);

    pid = fork();
    if (pid < 0) {
        error_exit("fork");
    } else if (pid == 0) {
        // Child Process
        int readfd = open(FIFO1, O_RDONLY); 
        int tempfd = open("temp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if (readfd == -1 || tempfd == -1)
            error_exit("child: open fifo1/temp_file");

        ssize_t bytes;
        while ((bytes = read(readfd, buffer, BUFFER_SIZE)) > 0) {
            write(tempfd, buffer, bytes);
        }

        close(readfd);
        close(tempfd);

        int writefd = open(FIFO2, O_WRONLY);
        tempfd = open("temp_file", O_RDONLY);

        if (writefd == -1 || tempfd == -1)
            error_exit("child: open fifo2/temp_file");

        while ((bytes = read(tempfd, buffer, BUFFER_SIZE)) > 0) {
            write(writefd, buffer, bytes);
        }

        close(writefd);
        close(tempfd);

        unlink("temp_file");
    } else {
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

        int readfd = open(FIFO2, O_RDONLY);
        int outfd = open(FILE2, O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if (readfd == -1 || outfd == -1)
            error_exit("parent: open fifo2/file2");

        while ((bytes = read(readfd, buffer, BUFFER_SIZE)) > 0) {
            write(outfd, buffer, bytes);
        }

        close(readfd);
        close(outfd);

        wait(NULL); //Waiting for child to finish

        //ending the timer and getting the transfer time
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_taken = (end.tv_sec - start.tv_sec) +
                            (end.tv_nsec - start.tv_nsec) / 1e9;
        
        //comparing the files
        int cmp_result = system("cmp original_file received_file");

        if (cmp_result == 0) {
            printf("Files match. Transfer successful.\n");
        } else {
            printf("Files do NOT match.\n");
        }

        printf("Time taken for round-trip transfer: %.3f seconds\n", time_taken);
    }
    system("ls -l");
    //Unlinking the fifos to free up memory
    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}
