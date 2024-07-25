/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:09:06 by alouriga          #+#    #+#             */
/*   Updated: 2024/07/21 18:03:23 by alouriga         ###   ########.fr       */
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


t_shell	*ft_lstlast(t_shell *lst)
{
	if (!lst)
		return (0);
	while (lst)
	{
		if (lst->next == NULL)
		{
			return (lst);
		}
		lst = lst->next;
	}
	return (0);
}
void	ft_lstadd_back(t_shell **lst, t_shell *new)
{
	if (!lst || !new)
		return ;
	if (ft_lstlast(*lst))
	{
		ft_lstlast(*lst)->next = new;
	}
	else
		*lst = new;
}