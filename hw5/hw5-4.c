#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*Write a program that calls fork() and then calls some form of
exec() to run the program /bin/ls. See if you can try all of the
variants of exec(), including (on Linux) execl(), execle(),
execlp(), execv(), execvp(), and execvpe(). Why do
you think there are so many variants of the same basic call?

l: arguments passed as a list of strings
v: arguments passed as an array of strings (vector)
p: path/s to search for the new running program
e: environment can be specified by the caller
*/


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
        //exec v = vector, l = list, e = env, p = Path suchen
        char *env[] = {"PATH=/bin:/usr/bin", NULL};
        char *args[2];
        args[0] = "/bin/ls";
        args[1] = (char *)NULL;
        //execl(args[0], args[0], (char *)NULL);
        //execle(args[0], args[0], (char *)NULL, env);
        //execlp(args[0], args[0], (char *)NULL);
        //execv(args[0], args);
        //execvp(args[0], args);
        //execvpe(args[0], args); // läuft nicht. WHY?
    }
    else

    {
        // parent goes down this path (main)
        int rc_wait = wait(NULL);
    }
    return 0;
}