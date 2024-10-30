/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 10:57:41 by alouriga          #+#    #+#             */
/*   Updated: 2024/10/30 04:46:16 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
# include <fcntl.h>

int    execute_path_2(char **command)
{
    int pid;
    t_shell *env = env_control(GET_ENV, 0, 0);
    char **td_env = convert_env_to_td_env(env);
    if (access(command[0], X_OK) == 0)
    {
            execve(command[0], command, td_env);
             write(2, command[0], ft_strlen(command[0]));
            write(2, ": Permission denied\n", 20);
			exit (126);
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
    int i;
    t_shell *env =  env_control(GET_ENV, 0, 0);

    p = find_path(env_control(GET_ENV, 0, 0));
    i = check_built_ins(command, env);
    if (command[0][0] == '/')
        execute_path_2(command);
    else if(i == 0)
		exit(0);
    else if (i == 2)
        exit(1);
    else
    {
        path = ft_split_2(p, ':');
        execute_command(command, path);
    }
}

// int   first_execution(char **command, t_commands *cmds, int *fd)
// {
// 	t_shell *env;
//     int pid = fork();
//     if (pid == -1)
//         return (pid);
//     if (pid != 0)
//     {
//         env =  env_control(GET_ENV, 0, 0);
//     }
//     if (pid == 0)
//     {
//         close(fd[0]);
//         dup2(fd[1], STDOUT_FILENO);
//         close(fd[1]);
//         if (check_the_redirection(cmds) == -1)
//         {
//             return(-1);
//         }
//         execution_first_command(command);
//     }
//     else
//     {
//         close(fd[1]);
//     }
// 	return (1);
// }

int   first_execution(char **command, t_commands *cmds, int *fd)
{
    t_shell *env =  env_control(GET_ENV, 0, 0);
    int bkp_0 = dup(0);
    int bkp_1 = dup(1);
    int pid = fork();
	if (!command[0])
    {
        dup2(bkp_1, 1);
        dup2(bkp_0, 0);
        close(bkp_0);
        close(bkp_1);
        return(0);
    }
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        if (check_the_redirection(cmds) == -1)
        {
            close(bkp_0);
            close(bkp_1);
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
        close(fd[1]);
    }
    return (1);
}
int   middle_execution(char **command, t_commands *cmds, int *fd, int s)
{
	t_shell *env;
	if (!command[0])
    {
		close(s);
        close(fd[0]);
        close(fd[1]);
        return(0);
    }
    pipe(fd);
    int pid = fork();
    if (pid == -3)
    {
        close(s);
        close(fd[0]);
        close(fd[1]);
        return (pid);
    }
    if (pid != 0)
    {
        env =  env_control(GET_ENV, 0, 0);
    }
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
        // print_open_fds();

        execution_first_command(command);
    }
    else
    {
        close(s);
        close(fd[1]);
    }
	return (1);
}

int    finale_execution(char **command, t_commands *cmds, int *fd, int s )
{
	t_shell *env;
	if (!command[0])
    {
		close(s);
        close(fd[0]);
        close(fd[1]);
        return(0);
    }
    int pid = fork();
    if (pid == -3)
    {
        close(s);
        close(fd[0]);
        close(fd[1]);
        return (pid);
    }
    if (pid != 0)
        env =  env_control(GET_ENV, 0, 0);
    if (!pid)
    {
        close(fd[1]);
        dup2(s, STDIN_FILENO);
        close(s);
        if (check_the_redirection(cmds) == -1)
            exit(1);
        execution_first_command(command);
        exit(127);
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
    int nb_of_nds;

	signal(SIGQUIT, SIG_DFL);
	g_signal_status = 1;
    i = 0;
    t_commands *tmp;
    int	save_fd = -1; 
    tmp = commands;
    if (!commands->next)
        pid_of_last_command = execution_commands(commands->command, commands);
    else
    {
        pipe(fd);
        nb_of_nds = ft_lstsize_2(tmp);
        if (first_execution(tmp->command, tmp ,fd) == -3)
        {
            write(2, "bash: fork: Resource temporarily unavailable\n", 46);
            exit_status(1, ADD);
            close(fd[0]);
            close(fd[1]);
            return;
        }
        save_fd = fd[0];
        tmp = tmp->next;
        nb_of_nds -= 1;
        while (i < nb_of_nds - 1)
        {
            if (middle_execution(tmp->command, tmp, fd, save_fd) == -3)
            {
                write(2, "bash: fork: Resource temporarily unavailable\n", 46);
                exit_status(1, ADD);
                close(fd[0]);
                close(fd[1]);
                return;
            }
            save_fd = fd[0];
            tmp = tmp->next;
            i++;
        }
        pid_of_last_command = finale_execution(tmp->command, tmp, fd, save_fd);
        if (pid_of_last_command == -3)
        {
            write(2, "bash: fork: Resource temporarily unavailable\n", 46);
            exit_status(1, ADD);
            close(fd[0]);
            close(fd[1]);
            return ;
        }
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
		signal(SIGQUIT, SIG_IGN);
        waitpid(pid_of_last_command, &status, 0);
        exit_status(WEXITSTATUS(status), ADD);
        
    }
    while(wait(NULL) != -1);
}
