/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:53:27 by akoutate          #+#    #+#             */
/*   Updated: 2024/11/01 10:51:02 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_first_word(t_data **lst, t_data *tmp)
{
	t_data	*new_lst;
	t_data	*tmp2;

	new_lst = NULL;
	if (tmp->to_split)
	{
		fill_lst(tmp->elem, &new_lst, 1);
		tmp2 = (*lst)->next;
		(*lst) = new_lst;
		while (new_lst->next)
			new_lst = new_lst->next;
		new_lst->next = tmp2;
	}
}

void	split_next_word(t_data *tmp)
{
	t_data	*new_lst;
	t_data	*tmp2;

	new_lst = NULL;
	if (tmp->next && tmp->next->to_split)
	{
		fill_lst(tmp->next->elem, &new_lst, 1);
		tmp2 = tmp->next->next;
		tmp->next = new_lst;
		while (new_lst->next)
			new_lst = new_lst->next;
		new_lst->next = tmp2;
	}
}

void	split_word(t_data **lst)
{
	t_data	*tmp;
	int		i;

	tmp = *lst;
	i = 0;
	while (tmp)
	{
		if (i == 0)
			split_first_word(lst, tmp);
		else
			split_next_word(tmp);
		i++;
		tmp = tmp->next;
	}
}
