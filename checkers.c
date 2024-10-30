/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:11:45 by akoutate          #+#    #+#             */
/*   Updated: 2024/10/30 19:14:53 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_if_to_expand_in_heredoc(t_data *lst)
{
	t_data	*tmp;

	while (lst)
	{
		if (lst->flag == HERE_DOC)
		{
			tmp = lst;
			if (lst->next && lst->next->flag == WHITE_SPACE)
				lst = lst->next;
			lst = lst->next;
			while (lst && (lst->flag == WORD
					|| lst->flag == QUOTE || lst->flag == DOUBLE_QUOTE))
			{
				if (lst->flag == QUOTE || lst->flag == DOUBLE_QUOTE)
				{
					tmp->expand_heredoc = 0;
					break ;
				}
				lst = lst->next;
			}
		}
		if (lst)
			lst = lst->next;
	}
}

int	check_space_middle(char *str)
{
	int	i;
	int	last;

	last = ft_strlen2(str) - 1;
	i = 0;
	while (str[i])
	{
		if ((str[i] == ' ' || str[i] == '\t') && (i != 0 && i != last))
			return (1);
		i++;
	}
	return (0);
}

void	check_for_ambiguous(t_data *lst)
{
	t_data	*tmp;

	while (lst)
	{
		tmp = lst;
		if (lst->flag == REDIR_IN || lst->flag == REDIR_OUT
			|| lst->flag == DREDIR_OUT)
		{
			if (lst->next && lst->next->flag == WHITE_SPACE)
				lst = lst->next;
			if (lst)
				lst = lst->next;
			if (!lst || lst->flag != WORD
				|| (lst->to_split && check_space_middle(lst->elem)))
				tmp->ambiguous = 1;
		}
		if (lst)
			lst = lst->next;
	}
}
