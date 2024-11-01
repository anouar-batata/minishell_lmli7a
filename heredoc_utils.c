/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 09:01:51 by akoutate          #+#    #+#             */
/*   Updated: 2024/11/01 09:02:29 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_doc_max(char **del)
{
	int	counter;

	counter = 0;
	while (del[counter])
		counter++;
	if (counter > 16)
	{
		write(2, "Error: maximum here-document count exceeded", 44);
		exit(2);
	}
}

void	expand_the_doc(char *prompt, char **str, t_shell *envi)
{
	t_data	*lst;

	lst = NULL;
	fill_lst(prompt, &lst, 1);
	expanding(lst, envi);
	free (prompt);
	prompt = "";
	while (lst)
	{
		prompt = ft_strjoin2(prompt, lst->elem);
		lst = lst->next;
	}
	*str = ft_strjoin2(*str, prompt);
	*str = ft_strjoin2(*str, "\n");
}
