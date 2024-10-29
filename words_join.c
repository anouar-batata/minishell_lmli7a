/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 23:17:10 by akoutate          #+#    #+#             */
/*   Updated: 2024/10/29 15:39:37 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_quote(t_data	*current_node, t_data *lst)
{
	int		in_quote;
	char	quote_type;
	int		first_quote;

	in_quote = 0;
	quote_type = 0;
	first_quote = 0;
	while (lst != current_node->next)
	{
		if (first_quote)
		{
			in_quote = 1;
			first_quote = 0;	
		}
		if ((lst->flag == QUOTE || lst->flag == DOUBLE_QUOTE) && !in_quote)
		{
			first_quote = 1;	
			quote_type = lst->flag;;
		}
		else if ((lst->flag == QUOTE || lst->flag == DOUBLE_QUOTE) && in_quote && quote_type == lst->flag)
		{
			in_quote = 0;
			quote_type = 0;
			first_quote = 0;
		}
		lst = lst->next;
	}
	return (in_quote);
}

void smart_strjoin(t_data *current, t_data *lst)
{
	t_data	*tmp;

	tmp = current;
	if (tmp->next)
		tmp = tmp->next;
	while (in_quote(tmp, lst))
	{
		current->elem = ft_strjoin2(current->elem, tmp->elem);
		tmp->to_remove = 1;
		tmp = tmp->next;
	}
	current->flag = -1;
}

void	join_word(t_data **lst)
{
	t_data *tmp;
	t_data *deleter;
	t_data *fr;
	tmp = *lst;	
	while (tmp)
	{
		if (in_quote(tmp, *lst) && ft_strlen2(tmp->elem))
		{
			smart_strjoin(tmp, *lst);
			tmp = tmp->next;
		}
		else if (tmp->next && (tmp->flag == QUOTE || tmp->flag == DOUBLE_QUOTE) && tmp->flag == tmp->next->flag)
		{
			tmp->elem = ft_strdup("");
			tmp->flag = -1;
			fr = tmp->next;
			tmp->next = tmp->next->next;
		}
		if (tmp)
			tmp = tmp->next;
	}
	tmp = *lst;
	while (tmp)
	{
		if (tmp->next && (tmp->next->to_remove || tmp->next->flag == QUOTE || tmp->next->flag == DOUBLE_QUOTE))
		{
			deleter = tmp->next;
			while (deleter && (deleter->to_remove || deleter->flag == QUOTE || deleter->flag == DOUBLE_QUOTE))
			{
				fr = deleter;
				deleter = deleter->next;
			}
			tmp->next = deleter;
		}
		tmp = tmp->next;
	}
	if (*lst && ((*lst)->to_remove || (*lst)->flag == QUOTE || (*lst)->flag == DOUBLE_QUOTE))
	{
		fr = *lst;
		*lst = (*lst)->next;
	}
	the_other_join(lst);
	tmp = *lst;
	while (tmp)
	{
		if (tmp->next && (tmp->next->to_remove || tmp->next->flag == QUOTE || tmp->next->flag == DOUBLE_QUOTE))
		{
			deleter = tmp->next;
			while (deleter && (deleter->to_remove || deleter->flag == QUOTE || deleter->flag == DOUBLE_QUOTE ))
			{
				fr = deleter;
				deleter = deleter->next;
			}
			tmp->next = deleter;
		}
		tmp = tmp->next;
	}
	if ((*lst) && ((*lst)->to_remove || (*lst)->flag == QUOTE || (*lst)->flag == DOUBLE_QUOTE))
	{
		fr = *lst;
		*lst = (*lst)->next;
	}
}
