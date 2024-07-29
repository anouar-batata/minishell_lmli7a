/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 01:03:21 by alouriga          #+#    #+#             */
/*   Updated: 2024/07/29 21:07:18 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_var(t_shell *env, t_shell **args)
{
	
}

void	ft_swap(t_shell *node1, t_shell *node2)
{
	char *tmp_k;
	char *tmp_v;
	
	tmp_k = node1->k;
	tmp_v = node1->v;
	node1->k = node2->k;
	node1->v = node2->v;
	node2->k = tmp_k;
	node2->v = tmp_v;
}

// 65    90
void  sort_env(t_shell **curr)
{
	int i;
	t_shell *tmp;

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

t_shell *env_copy(t_shell *env)
{
	t_shell *copy;
	t_shell *tmp;
	
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

void    ft_export(char **command)
{
	t_shell *export;
	int i;
	t_shell *env = env_copy(env_control(GET_ENV, 0, 0));
	i = 0;
	export = env;
	while (command[i])
		i++;
	if (i == 1)
	{
		sort_env(&export);
		while (export)
		{
			printf("declare -x %s=\"%s\"\n", export->k, export->v);
			export = export->next;
		}	
	}
	// else
	// 	add_var(env, command);
}