/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 10:57:41 by alouriga          #+#    #+#             */
/*   Updated: 2024/10/24 17:06:56 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    execute_path_2(char **command)
{
    int pid;
    t_shell *env = env_control(GET_ENV, 0, 0);
    char **td_env = convert_env_to_td_env(env);
    if (access(command[0], X_OK) == 0)
    {
            execve(command[0], command, td_env);
            perror(command[0]);
            exit(127);
    }
    else
    {
       perror("access");
       exit_status(127, ADD);
       return (-1);
    }
    return (pid);
}

void execution_first_command(char **command)
{
    char **path;
    char *p;
    int pid;
    t_shell *env =  env_control(GET_ENV, 0, 0);

    p = find_path(env_control(GET_ENV, 0, 0));
    if (command[0][0] == '/')
        execute_path_2(command);
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
            exit(1);
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
            exit(1);
        }
        execution_first_command(command);
        dup2(bkp_1, 1);
        dup2(bkp_0, 0);
        close(bkp_0);
        close(bkp_1);
        exit(127);
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
    int status = 0 ;
    int pid_of_last_command = 0;
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
    if (pid_of_last_command == -1) // to do
    {
        exit_status(1, ADD);
    }
    else if (pid_of_last_command == -2)
        exit_status(127, ADD);
    else
    {
        waitpid(pid_of_last_command, &status, 0);
        exit_status(WEXITSTATUS(status), ADD);
        
    }
    while(wait(NULL) != -1);
    printf("%d\n", exit_status(0, 0));
}
