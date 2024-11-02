/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:00:33 by akoutate          #+#    #+#             */
/*   Updated: 2024/11/02 01:14:56 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_to_list(char *str, int *index, t_data **lst)
{
	int		i;
	t_data	*new;
	char	*word;

	word = extract_env(index, str, 1, NULL);
	new = ft_lstnew5(word, ENV);
	if (!new)
		f_list();
	ft_lstadd_back5(lst, new);
}

void	add_a_node(t_data **lst, char *contain, int type, int *i)
{
	t_data	*new;

	new = ft_lstnew5(contain, type);
	ft_lstadd_back5(lst, new);
	*i += ft_strlen2(contain);
}

void	set_lst(char **str, t_data **lst, int *i)
{
	if ((*str)[*i] == '\'')
		add_a_node(lst, ft_strdup2("'"), QUOTE, i);
	else if ((*str)[*i] == '\"')
		add_a_node(lst, ft_strdup2("\""), DOUBLE_QUOTE, i);
	else if ((*str)[*i] == '<' && (*str)[*i + 1] == '<')
		add_a_node(lst, ft_strdup2("<<"), HERE_DOC, i);
	else if ((*str)[*i] == '<')
		add_a_node(lst, ft_strdup2("<"), REDIR_IN, i);
	else if ((*str)[*i] == '>' && (*str)[*i + 1] == '>')
		add_a_node(lst, ft_strdup2(">>"), DREDIR_OUT, i);
	else if ((*str)[*i] == '>')
		add_a_node(lst, ft_strdup2(">"), REDIR_OUT, i);
	else if ((*str)[*i] == '|')
		add_a_node(lst, ft_strdup2("|"), PIPE_LINE, i);
	else if ((*str)[*i] == 32 || ((*str)[*i] >= 9 && (*str)[*i] <= 13))
		add_space_to_list(&(*str)[*i], i, lst);
	else if ((*str)[*i] == '$')
		add_env_to_list(&(*str)[*i], i, lst);
	else
		add_word_to_list(&(*str)[*i], i, lst, 0);
}

void	fill_lst(char *str, t_data **lst, int pipe)
{
	t_data	*new;
	int		i;

	i = 0;
	while (str[i])
	{
		if (!pipe)
			set_lst(&str, lst, &i);
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
