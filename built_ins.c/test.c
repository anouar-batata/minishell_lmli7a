#include <unistd.h>
#include <stdio.h>

int main
{
    char    bufer[1024];

    getcwd(bufer, 1024);
    printf("[[pwd==%s]]\n", bufer);
}