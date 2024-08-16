/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:29:33 by akoutate          #+#    #+#             */
/*   Updated: 2024/08/16 23:41:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_handler(t_data *lst)
{
	while (lst)
	{
		while (lst && lst->flag != REDIR_IN && lst->flag != REDIR_OUT
			&& lst->flag != HERE_DOC && lst->flag != DREDIR_OUT)
			lst = lst->next;
		if (!lst)
			break ;
		lst = lst->next;
		while (lst && lst->flag == WHITE_SPACE)
			lst = lst->next;
		if (!lst || lst->flag == REDIR_IN || lst->flag == REDIR_OUT
			|| lst->flag == DREDIR_OUT
			|| lst->flag == HERE_DOC || lst->flag == PIPE_LINE)
			return (-1);
	}
	return (0);
}

int	pip_handler(t_data	*lst)
{
	t_data *beg;

	beg = lst;
	while (lst)
	{
		while (lst && lst->flag == WHITE_SPACE)
			lst = lst->next;
		if (lst && lst->flag == PIPE_LINE)
			return (-1);
		while (lst && (lst->flag != PIPE_LINE || in_quote(lst, beg)))
			lst = lst->next;
		if (!lst)
			break ;
		lst = lst->next;
		while (lst && lst->flag == WHITE_SPACE)
			lst = lst->next;
		if (!lst)
			return (-1);
	}
	return (0);
}

int	quote_handler(t_data *lst)
{
	t_data	*tmp;
	int		in_quote;
	char	quote_type;

	in_quote = 0;
	tmp = lst;
	while (tmp)
	{
		if (tmp->flag == DOUBLE_QUOTE || tmp->flag == QUOTE)
		{
			in_quote = -1;
			quote_type = tmp->flag;
			tmp = tmp->next;
			while (tmp && tmp->flag != quote_type)
				tmp = tmp->next;
			if (tmp)
			{
				in_quote = 0;
				tmp = tmp->next;
			}
		}
		else
			tmp = tmp->next;
	}
	return (in_quote);
}

int	parse_error(t_data *lst)
{
	if (quote_handler(lst) || pip_handler(lst) || redir_handler(lst))
	{
		fprintf(stderr, "bash: parse error\n");
		return (-1);
	}
	else
		return (0);
}
