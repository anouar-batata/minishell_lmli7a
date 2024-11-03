/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:28:45 by alouriga          #+#    #+#             */
/*   Updated: 2024/11/03 22:30:53 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_command(char **command, char **path)
{
	char	*first_join;
	char	*second_join;
	t_shell	*env;
	char	**td_env;
	int		i;

	i = 0;
	env = env_control(GET_ENV, 0, 0);
	td_env = convert_env_to_td_env(env);
	execute_command_helper(command, path);
	while (path[i++])
	{
		first_join = ft_strjoin(path[i], "/");
		second_join = ft_strjoin(first_join, command[0]);
		if (!access(second_join, F_OK))
		{
			execve(second_join, command, td_env);
			write(2, command[0], ft_strlen(command[0]));
			write(2, ": Permission denied\n", 20);
			exit (126);
		}
	}
	write(2, command[0], ft_strlen(command[0]));
	write(2, " : command not found\n", 21);
	exit(127);
}

char	*find_path(t_shell *env)
{
	while (env)
	{
		if (!ft_strcmp(env->k, "PATH"))
		{
			return (env->v);
		}
		env = env->next;
	}
	return (NULL);
}

int	execute_path(char **command)
{
	int		pid;
	t_shell	*env;
	char	**td_env;

	env = env_control(GET_ENV, 0, 0);
	td_env = convert_env_to_td_env(env);
	if (access(command[0], X_OK) == 0)
	{
		pid = fork();
		if (!pid)
		{
			execve(command[0], command, td_env);
			write(2, command[0], ft_strlen(command[0]));
			write(2, ": Permission denied\n", 20);
			exit (126);
		}
	}
	else
	{
		perror("access");
		exit_status(127, ADD);
		return (-1);
	}
	return (pid);
}

char	*ft_strchrrr(const char *s, int c)
{
	while (*s)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*(unsigned char *)s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}
