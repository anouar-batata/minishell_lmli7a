#include "libc.h"


int main()
{
    pid_t   child;

    child = fork();
    char *path[2] = {"./script_2.sh", NULL};
    if(child == -1)
        perror("child fails");
    if (!child)
        execve(path[0],path, NULL);
    perror("fails :");
}