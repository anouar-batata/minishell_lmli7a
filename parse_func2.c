/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_func2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 00:52:18 by akoutate          #+#    #+#             */
/*   Updated: 2024/11/02 01:14:53 by akoutate         ###   ########.fr       */
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

char	*extract_env(int *index, char *str, int i, char *word)
{
	while ((str[i] >= 65 && str[i] <= 90)
		|| (str[i] >= 97 && str[i] <= 122) || (str[i] >= 48 && str[i] <= 57))
	{
		if (((str[i] >= '0' && str[i] <= '9') || str[i] == '?') && i == 1)
			break ;
		i++;
	}
	if (str[i] == '$' && i == 1)
	{
		word = ft_strdup2("$$");
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
	return (word);
}
