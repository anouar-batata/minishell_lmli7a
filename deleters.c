/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deleters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:54:56 by akoutate          #+#    #+#             */
/*   Updated: 2024/10/31 17:34:04 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_spaces(t_data **lst)
{
	t_data	*tmp;
	t_data	*deleter;
	t_data	*fr;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->next && (tmp->next->flag == WHITE_SPACE))
		{
			deleter = tmp->next;
			while (deleter && (deleter->flag == WHITE_SPACE))
			{
				fr = deleter;
				deleter = deleter->next;
			}
			tmp->next = deleter;
		}
		tmp = tmp->next;
	}
	if ((*lst) && ((*lst)->flag == WHITE_SPACE))
	{
		fr = *lst;
		*lst = (*lst)->next;
	}
}

void	expanding_deleter(t_data **lst)
{
	t_data	*tmp;
	t_data	*deleter;
	t_data	*fr;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->next && (tmp->next->to_remove == 2))
		{
			deleter = tmp->next;
			while (deleter && (deleter->to_remove == 2))
			{
				fr = deleter;
				deleter = deleter->next;
			}
			tmp->next = deleter;
		}
		tmp = tmp->next;
	}
	if ((*lst) && ((*lst)->to_remove == 2))
	{
		fr = *lst;
		*lst = (*lst)->next;
	}
}
