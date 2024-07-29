/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:11:39 by akoutate          #+#    #+#             */
/*   Updated: 2024/07/29 05:59:50 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_space_to_list(char *str, int *index, t_data **lst)
{
	t_data *new;
	int		i;
	char *word;

	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	word = ft_substr(str, 0, i);

	*index += i;
	new = ft_lstnew(word, WHITE_SPACE);
	if (!new)
		f_list(lst);
	ft_lstadd_back(lst, new);
}

int is_word(char c)
{
	return (c == QUOTE || c == DOUBLE_QUOTE || c == WHITE_SPACE || c == ENV || c == PIPE_LINE || c == REDIR_IN || c == REDIR_OUT || c == '\t'); 
}


void add_word_to_list(char *str, int *index, t_data **lst)
{
	int	i;
	t_data *new;
	char *word;

	i = 0;
	while (!is_word(str[i]) && str[i])
		i++;
	word = ft_substr(str, 0, i);
	*index += i;
	new = ft_lstnew(word, WORD);
	if (!new)
		f_list(lst);
	ft_lstadd_back(lst, new);
}

void add_env_to_list(char *str, int *index, t_data **lst)
{
	int	i;
	t_data *new;
	char *word;

	i = 1;
	while (str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] !=  '$' && str[i] != '\'' && str[i] != '\"' && str[i] != 32 && (str[i] < 9 || str[i] > 13) && str[i])
		i++;
	word = ft_substr(str, 0, i);
	*index += i;
	new = ft_lstnew(word, ENV);
	if (!new)
		f_list(lst);
	ft_lstadd_back(lst, new);
}

void add_a_node(t_data **lst, char *contain, int type, int *i)
{
	t_data	*new;

	new = ft_lstnew(contain, type);
	if (!new)
		f_list(lst);
	ft_lstadd_back(lst, new);
	*i += ft_strlen(contain);
}

void fill_lst(char *str, t_data **lst)
{
	t_data *new;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			add_a_node(lst, "'", QUOTE, &i);
		else if (str[i] == '\"')
			add_a_node(lst, "\"", DOUBLE_QUOTE, &i);
		else if (str[i] == '<' && str[i + 1] == '<')
			add_a_node(lst, "<<", HERE_DOC, &i);
		else if (str[i] == '<')
			add_a_node(lst, "<", REDIR_IN, &i);
		else if (str[i] == '>' && str[i + 1] == '>')
			add_a_node(lst, ">>", DREDIR_OUT, &i);
		else if (str[i] == '>')
			add_a_node(lst, ">", REDIR_OUT, &i);
		else if (str[i] == '|')
			add_a_node(lst, "|", PIPE_LINE, &i);
		else if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			add_space_to_list(&str[i], &i, lst);
		else if (str[i] == '$')
			add_env_to_list(&str[i], &i, lst);
		else
			add_word_to_list(&str[i], &i, lst);
	}
}

int main()
{
	t_data *lst;
	char *rl;
	int i;

	while(1)
	{
		lst = NULL;
		rl = readline("slawishell: ");
		if (!rl)
			return (0);
		add_history(rl);
		fill_lst(rl, &lst);
		if (parse_error(lst))
			continue;
		free(rl);
		ft_lstiter(lst);
	}
	
    return (0);
}