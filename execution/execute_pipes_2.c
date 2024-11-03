/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:05:50 by alouriga          #+#    #+#             */
/*   Updated: 2024/11/03 22:15:41 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_path_2(char **command)
{
	int		pid;
	t_shell	*env;
	char	**td_env;

	env = env_control(GET_ENV, 0, 0);
	td_env = convert_env_to_td_env(env);
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

int	execute_programme_2(char **commands, char **path)
{
	char	*first_join;
	char	*second_join;
	t_shell	*env;
	char	**td_env;

	env = env_control(GET_ENV, 0, 0);
	td_env = convert_env_to_td_env(env);
	if (!access(commands[0], X_OK))
	{
		if (!ft_strchrrr(commands[0], '/'))
			commands[0] = ft_strjoin("./", commands[0]);
		execve(commands[0], commands, td_env);
		write(2, commands[0], ft_strlen(commands[0]));
		write(2, ": Permission denied\n", 20);
		exit (126);
	}
	else
	{
		perror(commands[0]);
		exit(127);
	}
	return (0);
}

void	utils_first_command(char **command, int i, char *p)
{
	int		pid;
	char	**path;

	if (i == 0)
		exit(0);
	else if (i == 2)
		exit(1);
	else if (!access(command[0], X_OK) && !p)
	{
		pid = execute_path(command);
		if (pid > 0)
			exit (0);
		else
			exit (1);
	}
	else
	{
		path = ft_split_2(p, ':');
		execute_command(command, path);
	}
}

void	execution_first_command(char **command)
{
	char	**path;
	char	*p;
	int		pid;
	int		i;
	t_shell	*env;

	env = env_control(GET_ENV, 0, 0);
	p = find_path(env_control(GET_ENV, 0, 0));
	i = check_built_ins(command);
	if (command[0][0] == '/')
		execute_path_2(command);
	else if (command[0] && command[0][0] != '/'
				&& ft_strchr_pro(command[0], "/"))
	{
		path = ft_split_2(p, ':');
		execute_programme_2(command, path);
		exit(0);
	}
	utils_first_command(command, i, p);
}

int	first_execution(char **command, t_commands *cmds, int *fd)
{
	int	red_in;
	int	red_out;
	int	pid;
	int	bkp_0;
	int	bkp_1;

	red_in = 0;
	red_out = 0;
	bkp_0 = dup(0);
	bkp_1 = dup(1);
	if (check_the_redirection(cmds, &red_out, &red_in) == -1)
		return (close_for_first(bkp_0, bkp_1, fd), -1);
	if (!command[0])
		return (close_for_first(bkp_0, bkp_1, fd), 0);
	pid = fork();
	if (pid == 0)
		check_the_outfile(red_out, fd, command);
	else
		close_for_first(bkp_0, bkp_1, fd);
	return (1);
}
