/*Write a program that calls fork() and then calls some form of
exec() to run the program /bin/ls. See if you can try all of the
variants of exec(), including (on Linux) execl(), execle(),
execlp(), execv(), execvp(), and execvpe(). Why do
you think there are so many variants of the same basic call?

the functions in the exec family differ in how the program to be
executed is found, in what form the arguments are specified,
and where the environment comes from.

v: vector/array to specify the argv[] array of the new program
l: arguments of the new program as a list
e: environment of the new program
p: path to search for the new program
*/

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
    else if (rc == 0)
    {
        char *env[] = {"PATH=/bin:/usr/bin", NULL};
        char *args[2];
        args[0] = "/bin/ls";
        args[1] = (char *)NULL;

        // execl("/bin/ls", "ls", (char *) NULL);
        // execle("/bin/ls", "ls", (char *) NULL, env);
        // execlp("/bin/ls", "ls", (char *) NULL);
        // execv("/bin/ls", args);
        // execvp("/bin/ls", args);
        // execvpe("/bin/ls", args); // keine POSIX
        // execve("/bin/ls", args, env);
    }
    return 0;
}