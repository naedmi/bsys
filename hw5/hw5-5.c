#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*Now write a program that uses wait() to wait for the child process
to finish in the parent. What does wait() return? What happens if
you use wait() in the child?*/

int main(int argc, char *argv[])
{
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        int rc_wait = wait(NULL);
        printf("child pid %d wait returncode %d\n", getpid(), rc_wait);
    }
    else
    {
        // returns the childs pid
        int rc_wait = wait(NULL);
        printf("parent pid %d wait returncode %d\n", getpid(), rc_wait);
    }
    return 0;
}