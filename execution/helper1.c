/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:25:45 by alouriga          #+#    #+#             */
/*   Updated: 2024/11/03 22:28:15 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s1)
{
	char	*cpy;
	size_t	i;

	if (!s1)
		return (NULL);
	cpy = (char *)smart_malloc((ft_strlen2(s1) + 1) * sizeof(char), ENVT);
	if (!cpy)
		exit(1);
	i = 0;
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_strjoin_3(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s2)
		return (s1);
	i = 0;
	j = 0;
	str = (char *)smart_malloc((ft_strlen2(s1)
				+ ft_strlen2(s2) + 1) * sizeof(char), ENVT);
	if (!str)
		exit(1);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	**convert_env_to_td_env(t_shell *env)
{
	int		size;
	char	*first_join;
	char	*second_join;
	char	**td_env;
	int		i;

	i = 0;
	size = ft_lstsize(env);
	td_env = smart_malloc((size + 1) * sizeof(char *), ENVT);
	if (!td_env)
		return (NULL);
	while (env)
	{
		first_join = ft_strjoin(env->k, "=");
		second_join = ft_strjoin_3(first_join, env->v);
		td_env[i] = ft_strdup(second_join);
		env = env->next;
		i++;
	}
	td_env[i] = NULL;
	return (td_env);
}

void	add_list(char **p, t_commands **curr)
{
	int			i;
	t_commands	*tmp;
	char		**res;

	i = 0;
	tmp = NULL;
	while (p[i] != NULL)
	{
		res = ft_split_2(p[i], ' ');
		tmp = ft_lstnew_2(res);
		ft_lstadd_back_2(curr, tmp);
		i++;
	}
}

void	execute_command_helper(char **command, char **path)
{
	if (!path)
	{
		write(2, command[0], ft_strlen(command[0]));
		write(2, " :  No such file or directory\n", 30);
		exit(127);
	}
	if (ft_strcmp(command[0], "\0") == 0)
	{
		write(2, " : command not found\n", 21);
		exit(127);
	}
}
