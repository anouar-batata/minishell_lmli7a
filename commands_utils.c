/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:05:21 by akoutate          #+#    #+#             */
/*   Updated: 2024/11/02 09:06:20 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_dels(t_data *lst)
{
	int	i;

	i = 0;
	while (1)
	{
		if (lst && lst->next && lst->next->flag == HERE_DOC)
		{
			i++;
			lst = lst->next->next;
		}
		else
		{
			if (lst)
				i++;
			break ;
		}
	}
	return (i);
}

char	**add_dels(t_data **lst)
{
	char	**dels;
	int		count;
	int		i;

	i = 0;
	count = count_dels(*lst);
	dels = smart_malloc((count + 1) * sizeof(char *), RL);
	if (!dels)
		exit(1);
	dels[i] = (*lst)->elem;
	i++;
	while (1)
	{
		if (i == count)
			break ;
		if (*lst && (*lst)->flag == HERE_DOC)
		{
			dels[i] = (*lst)->next->elem;
			i++;
		}
		*lst = (*lst)->next;
	}
	dels[i] = NULL;
	return (dels);
}

int	pip_counter(t_data *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->flag == PIPE_LINE)
			i++;
	}
	return (i + 1);
}

int	command_counter(t_data *lst)
{
	int	i;

	i = 0;
	while (lst && lst->flag != PIPE_LINE)
	{
		if (lst && lst->next && (lst->flag == REDIR_IN
				|| lst->flag == REDIR_OUT || lst->flag == DREDIR_OUT
				|| lst->flag == HERE_DOC))
		{
			lst = lst->next->next;
			continue ;
		}
		i++;
		lst = lst->next;
	}
	return (i);
}
