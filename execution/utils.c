/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 07:03:28 by alouriga          #+#    #+#             */
/*   Updated: 2024/09/24 16:21:09 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		i1;
	int		i2;
	char	*p;

	if (!s2)
		return (s1);
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