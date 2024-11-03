/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 08:41:19 by alouriga          #+#    #+#             */
/*   Updated: 2024/11/03 08:50:34 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_the_value(char *arg, t_shell *env, char **p)
{
	char	*key;
	char	*value;
	char	*resutl;
	char	*old_value;

	env = env_control(GET_ENV, 0, 0);
	p = ft_split_2(arg, '+');
	key = p[0];
	if (!search_env(env, key))
	{
		p = split_first_equal(arg, NULL, NULL, 0);
		old_value = get_old_value(key);
		value = p[1];
		resutl = ft_strjoin(old_value, value);
		env_control(EDIT_VALUE, key, resutl);
	}
	else
	{
		p = split_first_equal(arg, NULL, NULL, 0);
		value = p[1];
		if (value == NULL)
			env_control(ADD_NODE, key, "\0");
		else
			env_control(ADD_NODE, key, value);
	}
}

int	utils_export(char *arg, char **p, t_shell *env)
{
	int		k;
	t_shell	*tmp;

	k = 0;
	if (add_value(arg, env) == 1)
	{
		return (1);
	}
	p = split_first_equal(arg, NULL, NULL, 0);
	if (char_exists(p[0], '+'))
	{
		join_the_value(arg, NULL, NULL);
		return (1);
	}
	tmp = env;
	k = 0;
	p = split_first_equal(arg, NULL, NULL, 0);
	check_the_value(tmp, k, p);
	return (0);
}

void	ft_swap(t_shell *node1, t_shell *node2)
{
	char	*tmp_k;
	char	*tmp_v;

	tmp_k = node1->k;
	tmp_v = node1->v;
	node1->k = node2->k;
	node1->v = node2->v;
	node2->k = tmp_k;
	node2->v = tmp_v;
}

char	*get_old_value(char *target)
{
	t_shell	*env;

	env = env_control(GET_ENV, 0, 0);
	while (env)
	{
		if (ft_strcmp(env->k, target) == 0)
			return (env->v);
		env = env->next;
	}
	return (NULL);
}

void	replace_value(t_shell **env, char **arg)
{
	while (*env)
	{
		if (ft_strcmp((*env)->k, arg[0]))
		{
			env_control(REMOVE_NODE, arg[0], 0);
			env_control(ADD_NODE, arg[0], arg[1]);
			break ;
		}
		*env = (*env)->next;
	}
}
