/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 08:34:10 by alouriga          #+#    #+#             */
/*   Updated: 2024/11/03 08:49:56 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	manage_error(char *arg)
{
	write(2, arg, ft_strlen(arg));
	write(2, " : not a valid identifier\n", 26);
}

int	parse_arguments(char *arg, int i, int j)
{
	if (!ft_strlen(arg))
		return (manage_error(arg), 1);
	while (arg[i] != '\0')
	{
		if (arg[i] == '=' && i == 0)
			return (manage_error(arg), 1);
		if (arg[i] == '=')
			return (0);
		else
		{
			if (!((arg[i] >= 'A' && arg[i] <= 'Z') || (arg[i] == '_')
					|| (arg[i] >= 'a' && arg[i] <= 'z')) && i == 0)
				return (manage_error(arg), 1);
			if (!((arg[i] >= 'A' && arg[i] <= 'Z')
					|| (arg[i] >= 'a' && arg[i] <= 'z')
					|| (arg[i]) == '_' || (arg[i] >= '0' && arg[i] <= '9')
					|| (arg[i] == '+' && arg[i + 1] == '=')))
				return (manage_error(arg), 1);
		}
		i++;
	}
	return (0);
}

int	add_value(char *arg, t_shell *env)
{
	if (!char_exists(arg, '='))
	{
		if (!search_env(env, arg))
		{
			return (1);
		}
		else
		{
			env_control(ADD_NODE, arg, NULL);
			return (1);
		}
	}
	return (0);
}

int	char_exists(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

int	search_env(t_shell *env, char *str)
{
	while (env)
	{
		if (ft_strcmp(env->k, str) == 0)
			return (0);
		env = env->next;
	}
	return (1);
}
