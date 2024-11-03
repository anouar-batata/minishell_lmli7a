/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 09:19:30 by alouriga          #+#    #+#             */
/*   Updated: 2024/10/31 18:42:50 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_write(char **av, int i)
{
	while (av[i])
	{
		ft_putstr(av[i]);
		if (av[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

int	check_the_option(char **av, int j, int k, int i)
{
	while (av[i])
	{
		k = 1;
		j = 0;
		while (av[i][j] && av[i][0] == '-')
		{
			if (ft_strlen(av[i]) == 1)
				break ;
			if (av[i][j] == 'n')
				k++;
			j++;
		}
		if (k == j)
		{
			i++;
			continue ;
		}
		if (i == 0 && k != j)
			return (1);
		else
			return (ft_write(av, i), 0);
	}
	return (0);
}

int	echo(char **av)
{
	int	i;
	int	j;
	int	index;

	i = 0;
	j = 0;
	index = 1;
	while (av[++i])
	{
		if (av[i][j] == '-')
		{
			if (!check_the_option(&av[i], j, index, 0))
				return (1);
		}
		ft_putstr(av[i]);
		if (av[i + 1] != NULL)
			write(1, " ", 1);
	}
	printf("\n");
	return (0);
}
