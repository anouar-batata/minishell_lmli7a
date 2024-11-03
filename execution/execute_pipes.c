/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 10:57:41 by alouriga          #+#    #+#             */
/*   Updated: 2024/11/03 22:24:34 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	middle_execution(char **command, t_commands *cmds, int *fd, int s)
{
	int	red_in;
	int	red_out;
	int	bkp_0;
	int	bkp_1;
	int	pid;

	bkp_0 = dup(0);
	bkp_1 = dup(1);
	red_in = 0;
	red_out = 0;
	if (check_the_redirection(cmds, &red_out, &red_in) == -1)
		return (close_for_middle(bkp_1, bkp_0, fd), -1);
	pipe(fd);
	if (!command[0])
		return (close_pipe_bkp(bkp_0, bkp_1, fd, s), 0);
	pid = fork();
	if (pid == -1)
		return (close_pipe_bkp(bkp_0, bkp_1, fd, s), -3);
	if (pid == 0)
		exec_for_middle(command, s, fd, red_out);
	else
		close_for_middle_2(bkp_1, bkp_0, fd, s);
	return (1);
}

int	finale_execution(char **command, t_commands *cmds, int *fd, int s )
{
	int	red_out;
	int	red_in;
	int	bkp_0;
	int	bkp_1;
	int	pid;

	red_out = 0;
	red_in = 0;
	bkp_0 = dup(0);
	bkp_1 = dup(1);
	if (check_the_redirection(cmds, &red_out, &red_in) == -1)
		return (close_pipe_bkp(bkp_0, bkp_1, fd, s), -1);
	if (!command[0])
		return (close_pipe_bkp(bkp_0, bkp_1, fd, s), 0);
	pid = fork();
	if (pid == -1)
		return (close_pipe_bkp(bkp_0, bkp_1, fd, s), -3);
	if (!pid)
		check_the_infile(red_in, fd, command, s);
	else
		dup_bkp_close(bkp_0, bkp_1);
	return (pid);
}

void	exit_status_hundler(int pid_of_last_command, int status)
{
	if (pid_of_last_command == -1)
		exit_status(1, ADD);
	else if (pid_of_last_command == -2)
		exit_status(127, ADD);
	else
	{
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid_of_last_command, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				printf("Quit: 3\n");
			exit_status((WTERMSIG(status) + 128), ADD);
		}
		else
			exit_status(WEXITSTATUS(status), ADD);
	}
}

void	the_content(t_commands *tmp)
{
	int	i;

	i = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->command[i])
		{
			tmp->command[i] = ft_strdup(tmp->command[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

void	execute_pipes(t_commands *commands, int i, int status, int nb_of_nds)
{
	int			save_fd;
	int			fd[2];
	int			pid_of_command;
	t_commands	*tmp;
	int			index;

	signal(SIGQUIT, SIG_DFL);
	g_signal_status = 1;
	save_fd = -1;
	pid_of_command = 0;
	tmp = commands;
	the_content(tmp);
	if (!commands->next)
		pid_of_command = execution_commands(commands->command, commands, NULL);
	else
	{
		pid_of_command = execute_pipes_helper(tmp, fd, save_fd, nb_of_nds);
		if (pid_of_command == -5)
			return ;
	}
	close(fd[0]);
	close(fd[1]);
	exit_status_hundler(pid_of_command, status);
	while (wait(NULL) != -1)
		;
}
