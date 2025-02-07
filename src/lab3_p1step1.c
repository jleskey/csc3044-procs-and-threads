/**
 * @file lab3_p1step1.c
 * @author Joseph Leskey
 * @date 4 February 2025
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
    pid_t pid;

    while (1)
    {
        pid = fork();

        if (pid == 0)
        {
            // Child process
            printf("New child process: %d\n", getpid());
            // We don't want child processes to loop.
            break;
        }
        else if (pid > 0)
        {
            // Parent process
            sync();
        }
        else
        {
            // Error
            const int err = errno;
            sleep(0.5);
            fflush(stdout);
            perror("main");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
