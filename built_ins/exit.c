/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:56:29 by alouriga          #+#    #+#             */
/*   Updated: 2024/11/03 22:04:21 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	the_string(char *s)
{
	int	j;

	j = 0;
	while (s[j] != '\0')
	{
		if ((s[j] == '-' || s[j] == '+') && j != 0)
			return (1);
		j++;
	}
	return (0);
}

int	sign(char *arr)
{
	int	j;
	int	count_sing;

	j = 0;
	count_sing = 0;
	while (arr[j] != '\0')
	{
		if (arr[j] == '+' || arr[j] == '-')
			count_sing++;
		j++;
	}
	if (count_sing >= 2)
		return (1);
	return (0);
}

static int	check_ch(char *s)
{
	int	j;

	j = 0;
	while (s[j] != '\0')
	{
		if (!((s[j] >= '0' && s[j] <= '9')
				|| (s[j] == '+') || s[j] == '-'))
			return (1);
		j++;
	}
	return (0);
}

void	exit_by_number(char *av, int x)
{
	my_atoi(av, &x, 1);
	if (x == 1)
	{
		printf("exit\n");
		write(2, "error: numeric argument required \n", 33);
		exit(255);
	}
	else
	{
		printf("exit\n");
		exit((my_atoi(av, &x, 1) % 256));
	}
}

int	ft_exit(char **av, int i, int j, int index)
{
	int	x;

	x = 0;
	while (av[i++] != NULL)
		index++;
	if (index == 1)
	{
		printf("exit\n");
		exit(exit_status(0, 0));
	}
	if (check_ch(av[1]) == 1 || sign(av[1]) == 1
		|| the_string(av[1]) == 1 || av[1][0] == '\0')
		error_manage();
	i = 0;
	index = 0;
	while (av[i++])
		index++;
	if (index != 2)
	{
		exit_error();
		return (exit_status(1, ADD), -1);
	}
	else
		exit_by_number(av[1], x);
	return (0);
}
