#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*Write a slight modification of the previous program, this time us-
ing waitpid() instead of wait(). When would waitpid() be
useful?*/

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
        int rc_wait = waitpid(-1, NULL, 0); //-1: erstes Kind, 0: terminieren
        printf("parent pid %d wait returncode %d\n", getpid(), rc_wait);
    }
    return 0;
}