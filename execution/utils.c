/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 07:03:28 by alouriga          #+#    #+#             */
/*   Updated: 2024/11/03 21:57:53 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
		return (s2);
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

void	ft_lstadd_back_2(t_commands **lst, t_commands *new)
{
	t_commands	*last;

	if (!lst)
		return ;
	last = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (last -> next != NULL)
			last = last -> next;
		last -> next = new;
	}
}

t_commands	*ft_lstnew_2(char **command)
{
	t_commands	*p;

	p = (t_commands *)smart_malloc(sizeof(t_commands), RL);
	if (!p)
		exit (1);
	p ->command = command;
	p ->next = NULL;
	return (p);
}

int	ft_lstsize_2(t_commands *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (i);
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
