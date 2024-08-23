/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 07:03:28 by alouriga          #+#    #+#             */
/*   Updated: 2024/08/23 03:55:29 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		i1;
	int		i2;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	i1 = ft_strlen(s1);
	i2 = ft_strlen(s2);
	p = (char *)malloc(sizeof(char) * (i1 + i2 + 1));
	i = 0;
	if (!p)
		return (NULL);
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		p[i1++] = s2[i++];
	}
	p[i1] = '\0';
	return (p);
}

void    ft_lstadd_back_2(t_commands **lst, t_commands *new)
{
    t_commands    *last;

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

	p = (t_commands *)malloc( sizeof(t_commands));
	if (!p)
		return (NULL);
	p ->command = command;
	p ->next = NULL;
	return (p);
}
