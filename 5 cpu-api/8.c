/*Write a program that creates two children, and connects the stan-
dard output of one to the standard input of the other, using the
pipe() system call.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd[2];
    // fd[0]: read
    // fd[1]: write
    pipe(fd); // returns 0 on success, -1 on error

    int rc_1 = fork();

    if (rc_1 < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc_1 == 0) // child 1
    {
        dup2(STDOUT_FILENO, fd[1]); // close stdout, duplicate the output side of pipe to stdout
        char buff[50];
        while (read(STDIN_FILENO, buff, 1) > 0)
        {
            write(STDOUT_FILENO, buff, 1);
        }
        exit(0);
    }
    else // parent
    {
        int rc_2 = fork();

        if (rc_2 < 0)
        {
            fprintf(stderr, "fork failed\n");
            exit(1);
        }
        else if (rc_2 == 0) // child 2
        {
            dup2(STDIN_FILENO, fd[0]); // close stdin, duplicate the input side of pipe to stdin
            char buff[50];
            while(read(STDIN_FILENO, buff, 1) > 0)
            {
                write(STDOUT_FILENO, buff, 1);
            }
            exit(0);
        }
        wait(rc_2);
    }
    return 0;
}