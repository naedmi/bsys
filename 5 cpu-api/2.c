/*Write a program that opens a file (with the open() system call)
and then calls fork() to create a new process. Can both the child
and parent access the file descriptor returned by open()? What
happens when they are writing to the file concurrently, i.e., at the
same time?

they both can access the file descriptor. writing concurrently works (?).
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
     int fd = open("test.txt", O_RDONLY);
    // int fd = open("test.txt", O_WRONLY);
    char buff[255];
    int rc = fork();

    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0) // child (new process)
    {
         printf("Child process. read size: %ld\n", read(fd, buff, 254));
        // printf("Child process. write size: %ld\n", write(fd, "child\n", 6));
    }
    else // parent goes down this path (main)
    {
         printf("Parent process. read size: %ld\n", read(fd, buff, 254));
        // printf("Parent process. write size: %ld\n", write(fd, "parent\n", 7));
    }
    close(fd);
    return 0;
}