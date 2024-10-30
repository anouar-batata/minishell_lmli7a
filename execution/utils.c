/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 07:03:28 by alouriga          #+#    #+#             */
/*   Updated: 2024/10/30 10:21:11 by akoutate         ###   ########.fr       */
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
	p = (char *)smart_malloc(sizeof(char) * (i1 + i2 + 1),RL);
	i = 0;
	if (!p)
		exit (1);
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

	p = (t_commands *)smart_malloc( sizeof(t_commands), RL);
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