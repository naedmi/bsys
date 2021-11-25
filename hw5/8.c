/* Write a program that creates two children, and connects the stan-
dard output of one to the standard input of the other, using the
pipe() system call. */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc != 1)
    {
        fprintf(stderr, "Wrong input: %s", argv[1]);
        exit(1);
    }
    
    int fd[2];
    // fd[0]: read
    // fd[1]: write
    if (pipe(fd) == -1) { // returns 0 on success, -1 on error
        fprintf(stderr, "pipe failed\n");
        exit(1);
    } 

    int rc_1 = fork();

    if (rc_1 < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc_1 == 0) // child 1
    {
        dup2(STDOUT_FILENO, fd[1]); // close stdout, duplicate the output side of pipe to stdout
        char buff[6];
        while (read(STDIN_FILENO, buff, 6) > 0)
        {
            write(STDOUT_FILENO, buff, 6);
        }
        // close(STDIN_FILENO);
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
            char buff[6];
            while(read(STDIN_FILENO, buff, 6) > 0)
            {
                write(STDOUT_FILENO, buff, 6);
            }
            // close(STDOUT_FILENO);
            exit(0);
        }
        waitpid(rc_2, NULL, 0);
    }
    close(fd[0]);
    close(fd[1]);
    exit(0);
}