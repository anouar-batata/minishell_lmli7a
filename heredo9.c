/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredo9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 18:07:03 by akoutate          #+#    #+#             */
/*   Updated: 2024/10/25 22:01:22 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredo9(char **del, t_shell *envi, int to_expand)
{
	char *prompt;
	char *str;
	int i;
	t_data *lst;
	int fd;
	char *file_name;
	int counter;
	i = 0;
	str = "";
	while (1)
	{
		prompt = readline("> ");
		if (!prompt || !ft_strcmp_2(prompt, del[i]))
		{
			if (!del[i + 1])
				break;
			i++;
			continue;
		}
		if (!del[i + 1] && to_expand)
		{
			lst = NULL;
			fill_lst(prompt, &lst, 0);
			expanding(lst, envi);
			prompt = "";
			while (lst)
			{
				prompt = ft_strjoin2(prompt, lst->elem);
				lst = lst->next;
			}
			str = ft_strjoin2(str, prompt);
			str = ft_strjoin2(str, "\n");
		}
		else if (!del[i + 1])
		{
			str = ft_strjoin2(str, prompt);
			str = ft_strjoin2(str, "\n");
		}
	}
	counter = 0;
	prompt = "";
	while (!access((prompt = ft_strjoin2(del[i], ft_itoa(counter))), F_OK))
		counter++;
	fd = open(prompt, O_CREAT | O_RDWR | O_TRUNC, 0644);
	write(fd, str, ft_strlen2(str)); 
	close(fd);
	return (prompt);
}
