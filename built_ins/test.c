#include <libc.h>
// https://jan.newmarch.name/OS/l9_1.html
// https://github.com/bel-oirg/minishell/blob/main/Exec/command/exec.c

void    child(int *fd)
{
    char    *path;
    int pid2 = fork();
    path = "/usr/bin/wc";
    if (!pid2)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execve(path, (char *[3]){"wc", NULL}, NULL);
    }
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
}

int main(int ac, char *argv[])
{
    char    *path = "/bin/cat";
    int fd[2];
    pipe(fd);
    int copy_out = dup(STDOUT_FILENO);
    int pid = fork();

    if (!pid)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execve(path, (char *[3]){"cat", "Makefile", NULL}, NULL);
    }
    else
        child(fd);
    wait(NULL);
}

// #include <errno.h>
// errno