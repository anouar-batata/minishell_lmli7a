/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:56:29 by alouriga          #+#    #+#             */
/*   Updated: 2024/10/28 20:16:34 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	cheak_the_string(char *s)
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

long long	my_atoi(char *str, int *index)
{
	long long	result;
	int			sign;
	int			i;

	*index = 0;
	result = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((result > LLONG_MAX / 10)
			|| (result == LLONG_MAX / 10 && (str[i] - '0') > LLONG_MAX % 10))
		{
			*index = 1;
			return (sign * LLONG_MAX);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	ft_exit(char **av)
{
	int	i;
	int	j;
	int	x;
	int	index;

	i = 0;
	j = 1;
	x = 0;
	index = 0;
	while (av[i] != NULL)
	{
		index++;
		i++;
	}
	if (index == 1)
	{
		printf("exit\n");
		exit(exit_status(0, 0));
	}
	i = 0;
	if (check_ch(av[1]) == 1 || sign(av[1]) == 1 || cheak_the_string(av[1]) == 1)
	{
		perror("numeric argument required\n");
		exit(255);
	}
	i = 0;
	index = 0;
	while (av[i])
	{
		index++;
		i++;
	}
	if (index != 2)
	{
		perror("too many arguments\n");
	}
	else
	{
		my_atoi(av[1], &x);
		if (x == 1)
		{
			perror("numeric argument required \n");
			exit(255);
		}
		else
			exit(my_atoi(av[1], &x) % 256);
	}
}
