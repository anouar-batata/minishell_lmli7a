/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 21:47:47 by akoutate          #+#    #+#             */
/*   Updated: 2024/10/07 23:24:42 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//  echo $USER+$USER 
// > $a
// > ""
void	find_env(t_data *lst, t_shell *envi, t_data *beg)
{
	if (ft_strlen2(lst->elem) == 1 && ((lst->next && lst->next->flag != QUOTE && lst->next->flag != DOUBLE_QUOTE && !in_quote(lst, beg)) || !lst->next))
		return;
	while (envi)
	{
		if (!ft_strcmp_2(lst->elem + 1, envi->k))
		{
			free(lst->elem);
			lst->elem = ft_strdup(envi->v);
			if (!lst->elem)
				break;
			return;
		}
		envi = envi->next;
	}
	free(lst->elem);
	lst->to_remove = 1;
	lst->elem = ft_strdup("");
}

void expanding(t_data *lst, t_shell *envi)
{
	t_data	*tmp;
	char	quote_type;
	int		in_quote;
	
	quote_type = 0;
	in_quote = 0;
	tmp = lst; 
	while (tmp)
	{
		if (in_quote || tmp->flag == DOUBLE_QUOTE || tmp->flag == QUOTE)
		{
			if (!in_quote)
				quote_type = tmp->flag;
			in_quote = 1;
			tmp = tmp->next;
			while (tmp && tmp->flag != quote_type && tmp->flag != ENV)
				tmp = tmp->next;
			if (tmp && tmp->flag == ENV && quote_type == DOUBLE_QUOTE)
			{
				if (ft_strlen2(tmp->elem) > 1)
					find_env(tmp, envi, lst);	
				tmp->flag = WORD;
				continue ;
			}
			else if (tmp && tmp->flag == ENV)
			{
				tmp->flag = WORD;
				continue ;
			}
			if (tmp)
			{
				in_quote = 0;
				tmp = tmp->next;
			}
		}
		else
		{
			if (tmp->flag == ENV)
			{
				if (ft_strlen2(tmp->elem) != 0)
					find_env(tmp, envi, lst);
				tmp->flag = WORD;
				if (ft_strchr_pro(tmp->elem, " \t"))
					tmp->to_split = 1;
			}
			tmp = tmp->next;
		}
	}
}
