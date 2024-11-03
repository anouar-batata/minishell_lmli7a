/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 01:03:21 by alouriga          #+#    #+#             */
/*   Updated: 2024/11/03 08:49:12 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_the_value(t_shell *tmp, int k, char **p)
{
	while (tmp && k == 0)
	{
		if (ft_strcmp(p[0], tmp->k) == 0)
		{
			env_control(EDIT_VALUE, p[0], p[1]);
			k = 1;
		}
		tmp = tmp->next;
	}
	if (k == 0)
		env_control(ADD_NODE, p[0], p[1]);
}

void	*add_var(char **args, int i, int k, char **p)
{
	t_shell	*tmp;
	t_shell	*env;

	env = env_control(GET_ENV, 0, 0);
	while (args[i])
	{
		if (parse_arguments(args[i], 0, 0) == 1)
		{
			exit_status(-1, ADD);
			i++;
			continue ;
		}
		else
		{
			if (utils_export(args[i], p, env) == 1)
			{
				i++;
				continue ;
			}
		}
		i++;
	}
	return (NULL);
}

void	sort_env(t_shell **curr)
{
	int		i;
	t_shell	*tmp;

	i = 0;
	while (!i)
	{
		i = 1;
		tmp = *curr;
		while (tmp->next)
		{
			if (ft_strcmp(tmp->k, tmp->next->k) > 0)
			{
				ft_swap(tmp, tmp->next);
				i = 0;
			}
			tmp = tmp->next;
		}
	}
}

t_shell	*env_copy(t_shell *env)
{
	t_shell	*copy;
	t_shell	*tmp;

	copy = NULL;
	tmp = NULL;
	while (env)
	{
		tmp = ft_lstnew(env->k, env->v);
		ft_lstadd_back(&copy, tmp);
		env = env->next;
	}
	return (copy);
}

void	ft_export(char **command)
{
	t_shell	*export;
	int		i;
	t_shell	*env;

	env = env_copy(env_control(GET_ENV, 0, 0));
	i = 0;
	export = env;
	while (command[i])
		i++;
	if (i == 1)
	{
		if (!env)
			return ;
		sort_env(&export);
		while (export)
		{
			if (export->v == NULL)
				printf("declare -x %s\n", export->k);
			else
				printf("declare -x %s=\"%s\"\n", export->k, export->v);
			export = export->next;
		}
	}
	else
		add_var(&command[1], 0, 0, NULL);
}
