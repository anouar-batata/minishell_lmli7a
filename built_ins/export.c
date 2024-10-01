/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 01:03:21 by alouriga          #+#    #+#             */
/*   Updated: 2024/09/24 16:27:43 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://www.youtube.com/playlist?list=PLGU1kcPKHMKj5yA0RPb5AK4QAhexmQwrW

#include "../minishell.h"

int	parse_arguments(char *argument)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (argument[i] != '\0')
	{
		if (argument[i] == '=')
			return (0);
		else
		{
			if (!((argument[i] >= 'A' && argument[i] <= 'Z') || (argument[i] >= 'a' && argument[i] <= 'z')) && i == 0)
			{
				printf(" not a valid identifier\n");
				return (1);
			}
			if (!((argument[i] >= 'A' && argument[i] <= 'Z') || (argument[i] >= 'a' && argument[i] <= 'z') || (argument[i] >= '0' && argument[i] <= '9') || (argument[i] == '+' && argument[i + 1] == '=')))
			{
					printf(" not a valid identifier\n");
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int search_env(t_shell *env, char *str)
{
	while (env)
	{
		if (ft_strcmp(env->k, str) == 0)
			return (0);
		env = env->next;
	}
	return (1);
}



int	ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return (0);
		s++;
	}
	if (*(unsigned char *)s == (unsigned char)c)
		return (0);
	return (1);
}


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

char *get_old_value(char *target)
{
	t_shell *env = env_control(GET_ENV, 0, 0);
	while (env)
	{
		if (ft_strcmp(env->k, target) == 0)
			return (env->v);
		env = env->next;
	}
	return (NULL);
}

void	join_the_value(char *arg)
{
	char *key;
	char *value;
	char *resutl;
	char *old_value;
	t_shell *env = env_control(GET_ENV, 0, 0);
	char **p = ft_split_2(arg, '+');
	key = p[0];
	if (!search_env(env, key))
	{
		p = ft_split_2(arg, '=');
		old_value = get_old_value(key);
		value = p[1];
		resutl = ft_strjoin(old_value, value);
		env_control(EDIT_VALUE, key, resutl);
	}
	else
	{
		p = ft_split_2(arg, '=');
		value = p[1];
		if (value == NULL)
			env_control(ADD_NODE, key, "\0");
		else
			env_control(ADD_NODE, key, value);
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
		if (parse_arguments(args[i]) == 1)
		{
			i++;
			continue;
		}
		else
		{
			if (ft_strchr(args[i], '='))
			{
				
				if (!search_env(env, args[i]))
				{
					i++;
					continue;
				}
				else
					env_control(ADD_NODE, args[i], NULL);
			}
			if (!ft_strchr(args[i], '+'))
			{
				join_the_value(args[i]);
				i++;
				continue;
			}
			tmp = env;
			k = 0;
			p = split_first_equal(args[i]);
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
			{
					env_control(ADD_NODE, p[0], p[1]);
			}
		}
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
				printf("declare -x %s\n", export->k);
			else
				printf("declare -x %s=\"%s\"\n", export->k, export->v);
			export = export->next;
		}	
	}
	else
	{
		// parce_arguments(&command[1]);
		add_var(&command[1]);
	}
}
