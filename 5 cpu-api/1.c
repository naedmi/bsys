/*Write a program that calls fork(). Before calling fork(), have the
main process access a variable (e.g., x) and set its value to some-
thing (e.g., 100). What value is the variable in the child process?
What happens to the variable when both the child and parent change
the value of x?

child process copies the variable, changes in parent process don't 
affect value in child process.*/

#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int x = 100;
    int rc = fork();
    
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        printf("Child process. var: %d\n", x);
        x = 101;
        printf("Child process. var after change: %d\n", x);

    }
    else
    {
        printf("Parent process. var: %d\n", x);
        x = 99;
        printf("Parent process. var after change: %d\n", x);
    }
    return 0;
}