/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredo9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 18:07:03 by akoutate          #+#    #+#             */
/*   Updated: 2024/10/31 23:03:46 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredo9_handler(int sig)
{
	close(0);
	g_signal_status = 1;
	exit_status(1, ADD);
}

char	*heredo9(char **del, t_shell *envi, int to_expand, int command_counter)
{
	char	*prompt;
	char	*str;
	int		i;
	t_data	*lst;
	int		fd;
	char	*file_name;
	int		counter;
	int		save;

	signal(SIGINT, heredo9_handler);
	i = 0;
	str = "";
	prompt = NULL;
	save = dup(0);
	counter = 0;
	while (del[counter])
		counter++;
	if (counter > 16)
	{
		write(2, "Error: maximum here-document count exceeded", 44);
		exit(2);
	}

	while (1)
	{
		if (!g_signal_status)
			prompt = readline("> ");
		if (!prompt || !ft_strcmp_2(prompt, del[i]))
		{
			if (!del[i + 1])
				break ;
			free (prompt);
			prompt = NULL;
			i++;
			continue ;
		}
		if (!del[i + 1] && to_expand)
		{

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
			str = ft_strjoin2(str, prompt);
			str = ft_strjoin2(str, "\n");
			continue ;
		}
		else if (!del[i + 1])
		{
			str = ft_strjoin2(str, prompt);
			str = ft_strjoin2(str, "\n");
			free (prompt);
			continue ;
		}
		free (prompt);
	}
	if (!g_signal_status)
		free (prompt);
	counter = 0;
	prompt = "";
	if (!g_signal_status)
	{
		prompt = ft_strjoin2(del[i], ft_itoa(counter));
		while (!access(prompt, F_OK))
		{
			counter++;
			prompt = ft_strjoin2(del[i], ft_itoa(counter));
		}
		fd = open(prompt, O_CREAT | O_RDWR | O_TRUNC, 0644);
		write(fd, str, ft_strlen2(str));
		close(fd);
	}
	dup2(save, 0);
	close(save);
	return (prompt);
}
