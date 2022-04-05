#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int *data = (int *) calloc(0, 100);
    free(data);
    printf("%d", data[50]);
    return 0;
}