/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 08:35:24 by akoutate          #+#    #+#             */
/*   Updated: 2024/09/09 04:37:01 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back5(t_data **lst, t_data *nw)
{
	t_data	*temp;

	if (!lst)
		return ;
	if (!nw)
		return ;
	if (!*lst)
	{
		*lst = nw;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = nw;
}

void	ft_lstiter(t_data *node)
{
	t_data	*tmp;

	if (!node)
		return ;
	while (node)
	{
		tmp = node;
		node = node->next;
		free(tmp);
	}
	free (node);
}

void	ft_lstiter2(t_commands *node)
{
	t_commands	*tmp;

	if (!node)
		return ;
	while (node)
	{
		tmp = node;
		node = node->next;
		free(tmp);
	}
	free (node);
}

void    ft_lstadd_back2(t_shell **lst, t_shell *new)
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

void    ft_lstadd_back3(t_commands **lst, t_commands *new)
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