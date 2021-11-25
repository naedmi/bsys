/*Write another program using fork(). The child process should
print “hello”; the parent process should print “goodbye”. You should
try to ensure that the child process always prints first; can you do
this without calling wait() in the parent?

you can do it using signals.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    int rc = fork();
    
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0) // child (new process)
    {
        printf("hello\n");
        kill(getppid(), SIGCONT);
    }
    else // parent goes down this path (main)
    {
        kill(getpid(), SIGSTOP);
        printf("goodbye\n");
    }
    return 0;
}