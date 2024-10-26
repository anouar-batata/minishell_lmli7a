/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:11:39 by akoutate          #+#    #+#             */
/*   Updated: 2024/10/25 20:57:45 by akoutate         ###   ########.fr       */
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
	if (!new)
		f_list(lst);
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
	if (!new)
		f_list(lst);
	ft_lstadd_back5(lst, new);
}

void	add_env_to_list(char *str, int *index, t_data **lst)
{
	int		i;
	t_data	*new;
	char	*word;

	i = 1;
	while (str[i] != '|' && str[i] != '>' && str[i] != '<'
		&& str[i] !=  '$' && str[i] != '\'' && str[i] != '\"'
		&& str[i] != 32 && (str[i] < 9 || str[i] > 13) && str[i] && str[i] != '-'
		&& str[i] != ',' && str[i] != '+' && str[i] != '=' && str[i] != '?')
	{
		if (((str[i] >= '0' && str[i] <= '9') || str[i] == '?') && i == 1)
			break;
		i++;
	}
	if (str[i] == '$' && i == 1)
	{
		word = ft_strdup("$$");
		*index += 2;
	}
	else if (((str[i] >= '0' && str[i] <= '9') || str[i] == '?')&& i == 1)
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
	if (!new)
		f_list(lst);
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
	t_data *tmp;

	tmp = lst;
	while (tmp)
	{
		if (in_quote(tmp, lst) && tmp->flag != ENV)
			tmp->flag = WORD;
		tmp = tmp->next;
	}
}

void	check_if_to_expand_in_heredoc(t_data *lst)
{
	t_data *tmp;
	
	while (lst)
	{
		if (lst->flag == HERE_DOC)
		{
			tmp = lst;
			if (lst->next && lst->next->flag == WHITE_SPACE)
				lst = lst->next;
			lst = lst->next;
			while (lst && (lst->flag == WORD || lst->flag == QUOTE || lst->flag == DOUBLE_QUOTE))
			{
				if (lst->flag == QUOTE || lst->flag == DOUBLE_QUOTE)
				{
					tmp->expand_heredoc = 0;
					break;
				}
				lst = lst->next;
			}
		}
		if (lst)
			lst = lst->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*lst;
	char	*rl;
	int		i;
	t_commands *tmp;
	t_shell *envi = NULL;
    t_commands *command;
	char **command_list;
	char *prompt = NULL;
	int print_n = 0 ;
	i = 0;
    char **p;
    while (env[i] != NULL)
    {
        p = split_first_equal(env[i]);
        add(p, &envi);
        i++;
    }
    env_control(0, envi, NULL);
	exit_status(0, ADD);
	while (1)
	{
		lst = NULL;
		command = NULL;
		// prompt = ft_strjoin2("slawishell --[", get_env(envi , "USER"));
		// prompt = ft_strjoin2(prompt ,"@");
		// prompt = ft_strjoin2(prompt,  print_pwd(get_env(envi, "PWD"), envi));
		// prompt = ft_strjoin2(prompt, "]--\n~~> ");
		rl = readline("slawishell ~> ");
		if (!rl)
			return (0);
		if (!ft_strlen2(rl))
			continue ;
		add_history(rl);
		fill_lst(rl, &lst, 0);
		change_it_to_word(lst);
		if (parse_error(lst))
			continue;
		expanding(lst, envi);
        split_word(&lst);
		check_if_to_expand_in_heredoc(lst);
		join_word(&lst);
		// while (lst)
		// {
		// 	printf("elem: {%s}, flag: {%i}, to expand herdoc {%i}\n",lst->elem, lst->flag, lst->expand_heredoc);
		// 	lst = lst->next;
		// }
		// continue;
        make_a_list_for_louriga_aviable(&lst, &command, envi);
		if (command)
			execute_pipes(command);
		free(rl);
		ft_lstiter(lst);
		ft_lstiter2(command);
	}
	return (0);
}
