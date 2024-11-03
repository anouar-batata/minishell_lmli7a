/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:38:24 by alouriga          #+#    #+#             */
/*   Updated: 2024/11/03 22:41:14 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ambiguous_error(int fd)
{
	write(2, "error: ambiguous redirect\n", 26);
	close (fd);
}

int	open_files(int *fd, t_redir *curr)
{
	if (curr->redir_type == REDIR_OUT)
		*fd = open(curr->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (curr->redir_type == DREDIR_OUT)
		*fd = open(curr->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
		return (perror("Error: "), -1);
	return (0);
}

void	dup_for_outfile(int fd)
{
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	dup_for_infile(int fd)
{
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}
