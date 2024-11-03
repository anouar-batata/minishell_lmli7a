/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 05:43:45 by alouriga          #+#    #+#             */
/*   Updated: 2024/11/02 02:27:12 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_manage(void)
{
	printf("exit\n");
	write(2, "error: numeric argument required\n", 33);
	exit(255);
}

long long	my_atoi(char *str, int *index, int sign)
{
	long long	result;
	int			i;

	*index = 0;
	result = 0;
	i = 0;
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
