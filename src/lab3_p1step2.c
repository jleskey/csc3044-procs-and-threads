/**
 * @file lab3_p1step2.c
 * @author Joseph Leskey
 * @date 4 February 2025
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/resource.h>

// Note: The rlimit struct is already included in <sys/resources.h>.

int main(int argc, char const *argv[])
{
    pid_t pid;

    struct rlimit lim;

    printf("\n");

    // Set process limits
    if (argc > 2) {
        lim.rlim_cur = atoi(argv[1]);
        lim.rlim_max = atoi(argv[2]);

        if (!setrlimit(RLIMIT_NPROC, &lim)) {
            printf("Set process limits.\n");
        } else {
            perror("main");
        }
    }

    // Get process limits
    if(!getrlimit(RLIMIT_NPROC, &lim)) {
        printf("Process limit (soft): %ld\n", lim.rlim_cur);
        printf("Process limit (hard): %ld\n", lim.rlim_max);
    } else {
        perror("main");
    }

    printf("\n");

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
