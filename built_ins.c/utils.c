/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:09:06 by alouriga          #+#    #+#             */
/*   Updated: 2024/07/29 18:55:23 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int ft_strlen(const char *s)
{
    int i;

    i = 0;
    while(s[i] != '\0')
        i++;
    return (i);
}

t_shell	*ft_lstnew(char *k, char *v)
{
	t_shell	*p;

	p = (t_shell *)malloc( sizeof(t_shell));
	if (!p)
		return (NULL);
	p ->k = k;
	p ->v = v;
	p ->next = NULL;
	return (p);
}

int	ft_lstsize(t_shell *lst)
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


t_shell	*ft_lstlast(t_shell *lst)
{
	if (!lst || lst->next)
		return (0);
	// printf("[%p]\n", lst);
	while (lst->next)
	{
		// printf("******\n");
		// if (lst->next == NULL)
		// {
		// 	return (lst);
		// }
		// if (lst)
		printf("[%s]\n", lst->v);
		lst = lst->next;
	}
	return (lst);
}

void    ft_lstadd_back(t_shell **lst, t_shell *new)
{
    t_shell    *last;

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