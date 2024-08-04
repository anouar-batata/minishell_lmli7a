/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 01:03:21 by alouriga          #+#    #+#             */
/*   Updated: 2024/08/04 07:37:59 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_value(t_shell **env, char **arg)
{
	while(*env)
	{
		if (ft_strcmp((*env)->k, arg[0]))
		{
			env_control(REMOVE_NODE, arg[0], 0);
			env_control(ADD_NODE, arg[0], arg[1]);
			break;
		}
		*env = (*env)->next;
	}
}


void	*add_var(char **args)
{
	int i;
	char **p;
	t_shell *tmp;
	int k;
	i = 0;
	t_shell *env = env_control(GET_ENV, 0, 0);
	while (args[i])
	{
		tmp = env;
		k = 0;
		p = ft_split_2(args[i], '=');
		while (tmp && k == 0)
		{
			if (ft_strcmp(p[0], tmp->k) == 0)
			{
				replace_value(&env, p);
				k = 1;
			}
			tmp = tmp->next;
		}
		if (k == 0)
			env_control(ADD_NODE, p[0], p[1]);
		i++;
	}
	return (NULL);
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
	t_shell *en = env_control(GET_ENV, 0, 0);
	i = 0;
	export = env; 
	while (command[i])
		i++;
	if (i == 1)
	{
		sort_env(&export);
		while (export)
		{
			if (export->v == NULL)
				export->v = "";
			printf("declare -x %s=\"%s\"\n", export->k, export->v);
			export = export->next;
		}	
	}
	else
		add_var(&command[1]);
}