/*Write a slight modification of the previous program, this time us-
ing waitpid() instead of wait(). When would waitpid() be
useful?

if there are several childs and you want to make sure the parent
process continues after a specific one.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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
        printf("child pid %d\n", getpid());
    }
    else
    {
        int rc_wait = waitpid(-1, NULL, 0); // -1 to match any pid
        printf("parent pid %d - wait return code %d\n", getpid(), rc_wait);
    }
    return 0;
}