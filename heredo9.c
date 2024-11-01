/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredo9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 18:07:03 by akoutate          #+#    #+#             */
/*   Updated: 2024/11/01 23:48:21 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredo9_handler(int sig)
{
	close(0);
	g_signal_status = 1;
	exit_status(1, ADD);
	(void)sig;
}

int	func(char *del, t_dels data, char **str, char *prompt)
{
	if (!del && data.to_expand)
	{
		expand_the_doc(prompt, str, data.envi);
		return (-1);
	}
	else if (!del)
	{
		*str = ft_strjoin2(*str, prompt);
		*str = ft_strjoin2(*str, "\n");
		free (prompt);
		return (-1);
	}
	free (prompt);
	return (0);
}

char	*open_heredoc(char **del, int to_expand, t_shell *envi, int i)
{
	char	*prompt;
	char	*str;
	t_dels	del_struct;

	del_struct.to_expand = to_expand;
	del_struct.envi = envi;
	str = "";
	while (1)
	{
		prompt = NULL;
		if (!g_signal_status)
			prompt = readline("> ");
		if (!prompt || !ft_strcmp_2(prompt, del[i]))
		{
			if (!del[i++ + 1])
				break ;
			free (prompt);
			continue ;
		}
		if (func(del[i + 1], del_struct, &str, prompt))
			continue ;
	}
	if (!g_signal_status)
		free (prompt);
	return (str);
}

void	find_good_file(char **prompt)
{
	int	counter;

	counter = 0;
	*prompt = ft_strjoin2("/tmp/heredc", ft_itoa(counter));
	while (!access(*prompt, F_OK))
	{
		counter++;
		*prompt = ft_strjoin2("/tmp/heredc", ft_itoa(counter));
	}
}

char	*heredo9(char **del, t_shell *envi, int to_expand)
{
	char	*prompt;
	int		fd;
	int		save;
	char	*str;

	prompt = NULL;
	count_doc_max(del);
	signal(SIGINT, heredo9_handler);
	save = dup(0);
	str = open_heredoc(del, to_expand, envi, 0);
	if (!g_signal_status)
	{
		find_good_file(&prompt);
		fd = open(prompt, O_CREAT | O_RDWR | O_TRUNC, 0644);
		write(fd, str, ft_strlen2(str));
		close(fd);
	}
	return (dup2(save, 0), close(save), prompt);
}
