/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 10:57:41 by alouriga          #+#    #+#             */
/*   Updated: 2024/08/23 04:08:22 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void    *execute_command(char **command, char **path)
// {
//     char *first_join;
//     char *second_join;
//     int i;
    
//     i = 0;
//     while (path[i])
//     {
//         first_join = ft_strjoin(path[i], "/");
//         second_join = ft_strjoin(first_join, command[0]);
//         if (!access(second_join, X_OK))
//         {
//             execve(second_join, command, NULL);
//             return (NULL);
//         }
//         i++;
//     }
//     printf("command not found \n");
//     return (NULL);
// }

void execution_first_command(char **command)
{
    char **path;
    char *p;
    int pid;

    p = find_path(env_control(GET_ENV, 0, 0));
    if (command[0][0] == '/')
        execute_path(command);
    else
    {
           path = ft_split_2(p, ':');
            execute_command(command, path);
    }
}

void    first_execution(char **command, int *fd)
{
    int pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execution_first_command(command); // **fd = alloc(pipes);
        
    }
    wait(NULL);
}

void    middle_execution(char **command, int *fd)
{
    pipe(fd);
    int pid = fork();
    if (pid == 0)
    {
        dup2(fd[0], STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execution_first_command(command);
    }
}

void    finale_execution(char **command, int *fd)
{
    int pid = fork();
    if (!pid)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execution_first_command(command);
    }
}

void    execute_pipes(t_commands *commands)
{
    int i;
    int j = 1;
    int fd[2];
    pipe(fd);

    i = 0;
    t_commands *tmp;
    tmp = commands;
    // while (commands)
    // {
    //     commands = commands->next;
    //     i++;
    // }
        if (!commands->next)
            execution_commands(commands->command);
        else
        {
            first_execution(tmp->command, fd);
            tmp = tmp->next;
            while (tmp->next)
            {
                middle_execution(tmp->command, fd);
            }
            finale_execution(tmp->command, fd);
        }
    while(wait(NULL) != -1);
    close(fd[0]);
    close(fd[1]);
}
