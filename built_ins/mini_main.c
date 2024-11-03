/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:45:01 by alouriga          #+#    #+#             */
/*   Updated: 2024/11/03 15:25:41 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_built_ins_2(char **av)
{
	if (ft_strcmp(av[0], "env") == 0)
		return (ft_env(), 0);
	if (ft_strcmp(av[0], "echo") == 0)
		return (echo(av), 0);
	if (ft_strcmp(av[0], "export") == 0)
	{
		ft_export(av);
		if (exit_status(0, 0) == -1)
			return (2);
		return (0);
	}
	if (ft_strcmp(av[0], "cd") == 0)
	{
		if (ft_cd(av) == 2)
			return (exit_status(1, ADD), 2);
		return (0);
	}
	if (ft_strcmp(av[0], "exit") == 0)
	{
		if (ft_exit(av, 0, 1, 0) == -1)
			return (2);
		return (0);
	}
	return (1);
}

int	check_built_ins(char **av)
{
	int	i;

	if (ft_strcmp(av[0], "pwd") == 0)
	{
		pwd();
		if (exit_status(0, 0) == 1)
			return (2);
		return (0);
	}
	if (ft_strcmp(av[0], "unset") == 0)
	{
		ft_unset(av);
		if (exit_status(0, 0) == -1)
			return (2);
		return (0);
	}
	else
	{
		i = check_built_ins_2(av);
		if (i == 2)
			return (2);
		else if (i == 0)
			return (0);
	}
	return (1);
}

void	add(char **p, t_shell **envi)
{
	int		i;
	t_shell	*curr;

	i = 0;
	curr = ft_lstnew(p[0], p[1]);
	ft_lstadd_back(envi, curr);
}
