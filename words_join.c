/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 23:17:10 by akoutate          #+#    #+#             */
/*   Updated: 2024/08/14 07:51:53 by akoutate         ###   ########.fr       */
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
	char	*str;
	int		flag;

	flag = 0;

	tmp = current;
	if (tmp->next)
		tmp = tmp->next;
	while (in_quote(tmp, lst))
	{
		current->elem = ft_strjoin(current->elem, tmp->elem);
		tmp->elem = ft_strdup("");
		tmp = tmp->next;
	}
	current->flag = -1;
}

void	join_word(t_data *lst)
{
	t_data *tmp;

	tmp = lst;
	while (tmp)
	{
		if (in_quote(tmp, lst) && ft_strlen(tmp->elem))
		{
			smart_strjoin(tmp, lst);
		}
		tmp = tmp->next;
	}
}
