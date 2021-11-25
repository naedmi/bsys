#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*Write a program that creates two children, and connects the stan-
dard output of one to the standard input of the other, using the
pipe() system call.*/

int main(int argc, char *argv[])
{
    int pip[2];
    pipe(pip);
    int rc_1 = fork();
    if (rc_1 < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc_1 == 0) //fork 1
    {
        char text[] = "I am the first child";
        close(pip[0]);
        write(pip[1], text, (strlen(text) + 1));
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
        else if (rc_2 == 0) // second child
        {
            char buff[50];
            close(pip[1]);
            read(pip[0], buff, sizeof(buff));
            printf("Pipe from first child: %s\n", buff);
        }
    }
    return 0;
}