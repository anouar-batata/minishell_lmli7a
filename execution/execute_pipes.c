/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 10:57:41 by alouriga          #+#    #+#             */
/*   Updated: 2024/10/08 17:32:00 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execution_first_command(char **command)
{
    char **path;
    char *p;
    int pid;
    t_shell *env =  env_control(GET_ENV, 0, 0);

    p = find_path(env_control(GET_ENV, 0, 0));
    if (command[0][0] == '/')
        execute_path(command);
    else if(check_built_ins(command, env) == 0)
		exit(0);
    else
    {
           path = ft_split_2(p, ':');
            execute_command(command, path);
    }
}

int   first_execution(char **command, t_commands *cmds, int *fd)
{
	t_shell *env =  env_control(GET_ENV, 0, 0);
	int bkp_0 = dup(0);
    int bkp_1 = dup(1);
    int pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        if (check_the_redirection(cmds) == -1)
        {
            printf("No such file or directory\n");
            return(-1);
        }
        execution_first_command(command);
        dup2(bkp_1, 1);
        dup2(bkp_0, 0);
        close(bkp_0);
        close(bkp_1);
    }
    else
    {
        dup2(bkp_1, 1);
        dup2(bkp_0, 0);
        close(bkp_0);
        close(bkp_1);
        close(fd[1]);
    }
	return (1);
}
int   middle_execution(char **command, t_commands *cmds, int *fd, int s)
{
	t_shell *env =  env_control(GET_ENV, 0, 0);
	int bkp_0 = dup(0);
    int bkp_1 = dup(1);
    pipe(fd);
    int pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        dup2(s, STDIN_FILENO);
        close(s);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        if (check_the_redirection(cmds) == -1)
        {
            printf("No such file or directory\n"); //to do
            return(-1);
        }
        execution_first_command(command);
        dup2(bkp_1, 1);
        dup2(bkp_0, 0);
        close(bkp_0);
        close(bkp_1);
    }
    else
    {
        dup2(bkp_1, 1);
        dup2(bkp_0, 0);
        close(bkp_0);
        close(bkp_1);
        close(s);
        close(fd[1]);
    }
	return (1);
}

int    finale_execution(char **command, t_commands *cmds, int *fd, int s )
{
	t_shell *env =  env_control(GET_ENV, 0, 0);
	int bkp_0 = dup(0);
    int bkp_1 = dup(1);
	// if(check_built_ins(command, env) == 0)
	// 	return (0);
    int pid = fork();
    if (!pid)
    {
        close(fd[1]);
        dup2(s, STDIN_FILENO);
        close(s);
    if (check_the_redirection(cmds) == -1)
    {
        printf("No such file or directory\n");
        return(-1);
    }
        execution_first_command(command);
        dup2(bkp_1, 1);
        dup2(bkp_0, 0);
        close(bkp_0);
        close(bkp_1);
    }
    else
    {
        dup2(bkp_1, 1);
        dup2(bkp_0, 0);
        close(bkp_0);
        close(bkp_1);
    }
    return (pid);
}

void    execute_pipes(t_commands *commands)
{
    int i = 0;
    int j = 1;
    int fd[2];
    int status;
    int pid_of_last_command;
    pipe(fd);
    int nb_of_nds;

    i = 0;
    t_commands *tmp;
    int	save_fd = -1; 
    tmp = commands;
        if (!commands->next)
            pid_of_last_command = execution_commands(commands->command, commands);
        else
        {
            nb_of_nds = ft_lstsize_2(tmp);
           first_execution(tmp->command, tmp ,fd);
           save_fd = fd[0];
            tmp = tmp->next;
            nb_of_nds -= 1;
            while (i < nb_of_nds - 1)
            {
                middle_execution(tmp->command, tmp, fd, save_fd);
                save_fd = fd[0];
                tmp = tmp->next;
                i++;
            }
            pid_of_last_command = finale_execution(tmp->command, tmp, fd, save_fd);
        }
    close(fd[0]);
    close(fd[1]);
    // if (!commands->next)
    //     waitpid()
    waitpid(pid_of_last_command, &status, 0);
    // if(WIFEXITED(status))
    //     //
    // else if (WIFSIGNALED(status))
    // {
        
    // }
    exit_status(WEXITSTATUS(status), ADD);
    // fprintf(stderr,"STATUS: %i\n", exit_status(0, 0));
    
    while(wait(NULL) != -1);
}
