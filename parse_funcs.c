/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:00:33 by akoutate          #+#    #+#             */
/*   Updated: 2024/10/31 18:05:01 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_space_to_list(char *str, int *index, t_data **lst)
{
	t_data	*new;
	int		i;
	char	*word;

	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	word = ft_substr(str, 0, i);
	*index += i;
	new = ft_lstnew5(word, WHITE_SPACE);
	ft_lstadd_back5(lst, new);
}

int	is_word(char c)
{
	return (c == QUOTE || c == DOUBLE_QUOTE || c == WHITE_SPACE
		|| c == ENV || c == PIPE_LINE || c == REDIR_IN || c == REDIR_OUT
		|| c == '\t');
}

void	add_word_to_list(char *str, int *index, t_data **lst, int is_env)
{
	int		i;
	t_data	*new;
	char	*word;

	i = 0;
	if (!is_env)
	{
		while (!is_word(str[i]) && str[i])
			i++;
	}
	else
	{
		while (str[i] != ' ' && str[i] != '\t' && str[i] != ENV && str[i])
			i++;
	}
	word = ft_substr(str, 0, i);
	*index += i;
	new = ft_lstnew5(word, WORD);
	ft_lstadd_back5(lst, new);
}

void	add_env_to_list(char *str, int *index, t_data **lst)
{
	int		i;
	t_data	*new;
	char	*word;

	i = 1;
	while ((str[i] >= 65 && str[i] <= 90)
		|| (str[i] >= 97 && str[i] <= 122) || (str[i] >= 48 && str[i] <= 57))
	{
		if (((str[i] >= '0' && str[i] <= '9') || str[i] == '?') && i == 1)
			break ;
		i++;
	}
	if (str[i] == '$' && i == 1)
	{
		word = ft_strdup("$$");
		*index += 2;
	}
	else if (((str[i] >= '0' && str[i] <= '9')
			|| str[i] == '?') && i == 1)
	{
		word = ft_substr(str, 0, 2);
		*index += 2;
	}
	else
	{
		word = ft_substr(str, 0, i);
		*index += i;
	}
	new = ft_lstnew5(word, ENV);
	if (!new)
		f_list(lst);
	ft_lstadd_back5(lst, new);
}

void	add_a_node(t_data **lst, char *contain, int type, int *i)
{
	t_data	*new;

	new = ft_lstnew5(contain, type);
	ft_lstadd_back5(lst, new);
	*i += ft_strlen2(contain);
}

void	fill_lst(char *str, t_data **lst, int pipe)
{
	t_data	*new;
	int		i;

	i = 0;
	while (str[i])
	{
		if (!pipe)
		{
			if (str[i] == '\'')
				add_a_node(lst, ft_strdup("'"), QUOTE, &i);
			else if (str[i] == '\"')
				add_a_node(lst, ft_strdup("\""), DOUBLE_QUOTE, &i);
			else if (str[i] == '<' && str[i + 1] == '<')
				add_a_node(lst, ft_strdup("<<"), HERE_DOC, &i);
			else if (str[i] == '<')
				add_a_node(lst, ft_strdup("<"), REDIR_IN, &i);
			else if (str[i] == '>' && str[i + 1] == '>')
				add_a_node(lst, ft_strdup(">>"), DREDIR_OUT, &i);
			else if (str[i] == '>')
				add_a_node(lst, ft_strdup(">"), REDIR_OUT, &i);
			else if (str[i] == '|')
				add_a_node(lst, ft_strdup("|"), PIPE_LINE, &i);
			else if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
				add_space_to_list(&str[i], &i, lst);
			else if (str[i] == '$')
				add_env_to_list(&str[i], &i, lst);
			else
				add_word_to_list(&str[i], &i, lst, 0);
		}
		else
		{
			if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
				add_space_to_list(&str[i], &i, lst);
			else if (str[i] == '$')
				add_env_to_list(&str[i], &i, lst);
			else
				add_word_to_list(&str[i], &i, lst, 1);
		}
	}
}

void	change_it_to_word(t_data *lst)
{
	t_data	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (in_quote(tmp, lst) && tmp->flag != ENV)
			tmp->flag = WORD;
		tmp = tmp->next;
	}
}
