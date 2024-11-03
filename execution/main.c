/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:54:38 by alouriga          #+#    #+#             */
/*   Updated: 2024/11/03 22:37:29 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_bkp_close(int bkp_0, int bkp_1)
{
	dup2(bkp_1, 1);
	dup2(bkp_0, 0);
	close(bkp_0);
	close(bkp_1);
}

int	execute_programme(char **commands, char **path)
{
	int		pid;
	t_shell	*env;
	char	**td_env;

	env = env_control(GET_ENV, 0, 0);
	td_env = convert_env_to_td_env(env);
	pid = fork();
	if (!pid)
	{
		if (!access(commands[0], F_OK))
		{
			{
				if (!ft_strchrrr(commands[0], '/'))
					commands[0] = ft_strjoin("./", commands[0]);
				execve(commands[0], commands, td_env);
				write(2, commands[0], ft_strlen(commands[0]));
				write(2, ": Permission denied\n", 20);
				exit(126);
			}
		}
		perror(commands[0]);
		exit(127);
	}
	return (pid);
}

int	execute_commands_helper(char **cmd, t_commands *cmds,
	int bkp_0, int bkp_1)
{
	int		pid;
	char	*p;
	char	**path;

	p = find_path(env_control(GET_ENV, 0, 0));
	if (check_the_redirection(cmds, 0, 0) == -1)
		return (dup_bkp_close(bkp_0, bkp_1), -1);
	if (!cmd[0])
		return (dup_bkp_close(bkp_0, bkp_1), 0);
	if (cmd[0] && (cmd[0][0] == '/'))
	{
		pid = execute_path(cmd);
		dup_bkp_close(bkp_0, bkp_1);
		if (pid > 0)
			return (pid);
		else
			return (-2);
	}
	else if (cmd[0] && cmd[0][0] != '/' && ft_strchr_pro(cmd[0], "/"))
	{
		path = ft_split_2(p, ':');
		dup_bkp_close(bkp_0, bkp_1);
		return (execute_programme(cmd, path));
	}
	return (-3);
}

int	execute_commands_helper_2(int i, char **commands, int bkp_0, int bkp_1)
{
	int		pid;
	char	*p;

	p = find_path(env_control(GET_ENV, 0, 0));
	if (i == 0)
		return (dup_bkp_close(bkp_0, bkp_1), 255);
	else if (i == 2)
		return (dup_bkp_close(bkp_0, bkp_1), -1);
	else if (!access(commands[0], X_OK) && !p)
	{
		pid = execute_path(commands);
		dup_bkp_close(bkp_0, bkp_1);
		if (pid > 0)
			return (pid);
		else
			return (-2);
	}
	return (-3);
}

int	execution_commands(char **commands, t_commands *cmds, char **path)
{
	char	*p;
	int		pid;
	int		i;
	int		bkp_0;
	int		bkp_1;

	bkp_0 = dup(0);
	bkp_1 = dup(1);
	p = find_path(env_control(GET_ENV, 0, 0));
	path = ft_split_2(p, ':');
	pid = execute_commands_helper(commands, cmds, bkp_0, bkp_1);
	if (pid != -3)
		return (pid);
	i = check_built_ins(commands);
	pid = execute_commands_helper_2(i, commands, bkp_0, bkp_1);
	if (pid != -3)
		return (pid);
	else
	{
		pid = fork();
		if (!pid)
			execute_command(commands, path);
		dup_bkp_close(bkp_0, bkp_1);
		return (pid);
	}
}
