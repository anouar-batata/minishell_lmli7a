/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:53:55 by alouriga          #+#    #+#             */
/*   Updated: 2024/11/03 15:28:56 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_parce(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '\0')
	{
		if (!((av[i] >= 'A' && av[i] <= 'Z') || (av[i] == '_')
				|| (av[i] >= 'a' && av[i] <= 'z')) && i == 0)
		{
			manage_error(av);
			return (exit_status(1, ADD), 1);
		}
		if (!((av[i] >= 'A' && av[i] <= 'Z')
				|| (av[i] >= 'a' && av[i] <= 'z')
				|| (av[i]) == '_' || (av[i] >= '0' && av[i] <= '9')))
		{
			manage_error(av);
			return (exit_status(1, ADD), 1);
		}
		i++;
	}
	return (0);
}

void	remove_by_unset(t_shell *curr, t_shell *env, char *av, int i)
{
	while (av && curr)
	{
		i = 2;
		if (ft_strcmp(av, curr->k) == 0)
		{
			if (!ft_strcmp(curr->k, "_"))
				i++;
			else
			{
				env_control(-1, curr->k, NULL);
				i = 0;
			}
		}
		if (i == 0)
			curr = env;
		else
			curr = curr->next;
	}
}

int	ft_unset(char **av)
{
	int		i;
	int		index;
	int		j;
	t_shell	*curr;
	t_shell	*env;

	i = 1;
	j = 0;
	index = 0;
	env = env_control(GET_ENV, 0, 0);
	while (av[i] != NULL)
	{
		if (unset_parce(av[i]) == 1)
		{
			exit_status(-1, ADD);
			i++;
			continue ;
		}
		curr = env;
		remove_by_unset(curr, env, av[i], index);
		i++;
	}
	return (0);
}
