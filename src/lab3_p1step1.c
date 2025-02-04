/**
 * @file lab3_p1step1.c
 * @author Joseph Leskey
 * @date 4 February 2025
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

int childCount = 0;

void printStopMessage();
void handleSigInt(int s);

int main()
{
    // We want to handle SIGINT graciously.
    signal(SIGINT, handleSigInt);

    pid_t pid;

    while (1)
    {
        pid = fork();

        if (pid == 0)
        {
            // Child process
            printf("New child process: %d\n", getpid());
            // Avoid much suffering.
            exit(EXIT_SUCCESS);
        }
        else if (pid > 0)
        {
            // Parent process
            childCount++;
            sync();
        }
        else
        {
            // Error
            const int err = errno;
            printStopMessage();
            fprintf(stderr, "Forking failed: %d %s\n", err, strerror(err));
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}

void printStopMessage() {
    printf("\nTotal children: %d\n", childCount);
}

void handleSigInt(int s) {
    printStopMessage();
    exit(EXIT_SUCCESS);
}
