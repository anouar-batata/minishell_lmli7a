/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 21:47:47 by akoutate          #+#    #+#             */
/*   Updated: 2024/10/29 21:25:08 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr2(const char *s, int c)
{
	size_t			i;
	char			cc;
	
	cc = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i++;
	}
	if (cc == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

int	check_if_del(t_data *lst)
{
	while (lst)
	{
		if (lst->flag == REDIR_IN || lst->flag == REDIR_OUT || lst->flag == PIPE_LINE
			|| lst->flag == DREDIR_OUT)
			break;
		else if (lst->flag == HERE_DOC)
			return (0);
		else if (lst->flag == WHITE_SPACE && lst->prev->flag != HERE_DOC)
			break;
		lst = lst->prev;
	}
	return (1);
}

void	find_env(t_data *lst, t_shell *envi, t_data *beg, int to_remove)
{
	if (ft_strlen2(lst->elem) == 1 && ((lst->next && lst->next->flag != QUOTE && lst->next->flag != DOUBLE_QUOTE && !in_quote(lst, beg)) || !lst->next))
		return;
	if (!ft_strcmp_2(lst->elem, "$?"))
	{
		free(lst->elem);
		lst->elem = ft_itoa(exit_status(0, 0));
		return;
	}
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
	lst->to_remove = to_remove;
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
				if (ft_strlen2(tmp->elem) > 1 && check_if_del(tmp))
					find_env(tmp, envi, lst, 0);	
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
				if (ft_strlen2(tmp->elem) != 0 && check_if_del(tmp))
					find_env(tmp, envi, lst, 1);
				tmp->flag = WORD;

				if (ft_strchr2(tmp->elem, ' ') || ft_strchr2(tmp->elem, '\t'))
					tmp->to_split = 1;
			}
			tmp = tmp->next;
		}
	}
}
