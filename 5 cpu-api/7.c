/* Write a program that creates a child process, and then in the child
closes standard output (STDOUT FILENO). What happens if the child
calls printf() to print some output after closing the descriptor?

no output. */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    if(argc != 1)
    {
        fprintf(stderr, "Wrong input: %s", argv[1]);
        exit(1);
    }
    
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        close(STDOUT_FILENO); // closes standard output
        printf("child\n");
    }
    else
    {
        wait(NULL);
        printf("parent\n");
    }
    return 0;
}