/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:42:01 by alouriga          #+#    #+#             */
/*   Updated: 2024/11/03 22:41:05 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_out_file(t_commands *command, int *red, int i)
{
	t_redir	*curr;
	int		fd;
	int		index;

	fd = -1;
	curr = command->redir_lst;
	index = 0;
	while (curr && index <= i)
	{
		if (!curr->file && curr->ambiguous)
			return (ambiguous_error(fd), -1);
		if (curr->redir_type == REDIR_OUT || curr->redir_type == DREDIR_OUT)
		{
			if (fd != -1)
				close(fd);
			if (red)
				*red = 1;
			if (open_files(&fd, curr) == -1)
				return (-1);
		}
		curr = curr->next;
		index++;
	}
	dup_for_outfile(fd);
	return (0);
}

int	open_to_infile_2(t_redir *curr, t_commands *command
					, int *red_out, int index)
{
	char	*temp;
	int		fd;

	fd = open(curr->file, O_RDONLY);
	if (fd == -1)
	{
		if (check_out_file(command, red_out, index) == -1)
			return (close(fd), -1);
		return (perror("Error: "), -1);
	}
	if (curr->to_close)
	{
		temp = ft_strjoin("./", curr->file);
		unlink(temp);
	}
	return (fd);
}

void	check_for_red_in(int fd, int *red_in)
{
	if (fd != -1)
		close(fd);
	if (red_in)
		*red_in = 1;
}

int	for_infile(t_commands *command, int *red_out, int *red_in, int *fd)
{
	int		index;
	t_redir	*curr;

	index = 0;
	curr = command->redir_lst;
	while (curr)
	{
		if (curr->redir_type == REDIR_IN)
		{
			if (!curr->file && curr->ambiguous)
			{
				if (check_out_file(command, red_out, index) == -1)
					return (close(*fd), -1);
				return (ambiguous_error(*fd), -1);
			}
			check_for_red_in(*fd, red_in);
			*fd = open_to_infile_2(curr, command, red_out, index);
			if (*fd == -1)
				return (-1);
		}
		curr = curr->next;
		index++;
	}
	return (0);
}

int	check_the_redirection(t_commands *command, int *red_out, int *red_in)
{
	t_redir	*curr;
	int		fd;
	int		index;

	fd = -1;
	index = 0;
	curr = command->redir_lst;
	if (for_infile(command, red_out, red_in, &fd) == -1)
		return (-1);
	dup_for_infile(fd);
	if (check_out_file(command, red_out, index) == -1)
		return (close(fd), -1);
	return (0);
}
