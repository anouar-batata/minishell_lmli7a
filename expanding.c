/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 21:47:47 by akoutate          #+#    #+#             */
/*   Updated: 2024/11/01 07:55:21 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_del(t_data *lst)
{
	while (lst)
	{
		if (lst->flag == REDIR_IN || lst->flag == REDIR_OUT
			|| lst->flag == PIPE_LINE
			|| lst->flag == DREDIR_OUT)
			break ;
		else if (lst->flag == HERE_DOC)
			return (0);
		else if (lst->flag == WHITE_SPACE
			&& (lst->prev && lst->prev->flag != HERE_DOC))
			break ;
		lst = lst->prev;
	}
	return (1);
}

void	find_env(t_data *lst, t_shell *envi, t_data *beg, int to_remove)
{
	if (ft_strlen2(lst->elem) == 1 && ((lst->next
				&& lst->next->flag != QUOTE && lst->next->flag != DOUBLE_QUOTE
				&& !in_quote(lst, beg)) || !lst->next))
		return ;
	if (!ft_strcmp_2(lst->elem, "$?"))
	{
		lst->elem = ft_itoa(exit_status(0, 0));
		return ;
	}
	while (envi)
	{
		if (!ft_strcmp_2(lst->elem, "$"))
			break ;
		if (!ft_strcmp_2(lst->elem + 1, envi->k))
		{
			lst->elem = ft_strdup2(envi->v);
			if (!lst->elem)
				break ;
			return ;
		}
		envi = envi->next;
	}
	lst->to_remove = to_remove;
	lst->elem = ft_strdup2("");
}

int	expand_inside_quotes(t_data **tmp, t_data *lst,
	t_shell *envi, int quote_type)
{
	*tmp = (*tmp)->next;
	while ((*tmp) && (*tmp)->flag != quote_type && (*tmp)->flag != ENV)
		(*tmp) = (*tmp)->next;
	if ((*tmp) && (*tmp)->flag == ENV && quote_type == DOUBLE_QUOTE)
	{
		if (ft_strlen2((*tmp)->elem) > 1 && check_if_del((*tmp)))
			find_env((*tmp), envi, lst, 0);
		(*tmp)->flag = WORD;
		return (-1);
	}
	else if ((*tmp) && (*tmp)->flag == ENV)
	{
		(*tmp)->flag = WORD;
		return (-1);
	}
	return (0);
}

void	expand_outside_quotes(t_data **tmp, t_data *lst, t_shell *envi)
{
	if ((*tmp)->flag == ENV)
	{
		if (ft_strlen2((*tmp)->elem) != 0 && check_if_del(*tmp))
			find_env(*tmp, envi, lst, 1);
		(*tmp)->flag = WORD;
		if (ft_strchr2((*tmp)->elem, ' ') || ft_strchr2((*tmp)->elem, '\t'))
			(*tmp)->to_split = 1;
	}
	*tmp = (*tmp)->next;
}

void	expanding(t_data *lst, t_shell *envi)
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
			if (expand_inside_quotes(&tmp, lst, envi, quote_type))
				continue ;
			if (tmp)
			{
				in_quote = 0;
				tmp = tmp->next;
			}
		}
		else
			expand_outside_quotes(&tmp, lst, envi);
	}
}
