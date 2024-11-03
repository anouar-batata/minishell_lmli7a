/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:16:09 by alouriga          #+#    #+#             */
/*   Updated: 2024/11/03 22:21:11 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_for_first(int bkp_0, int bkp_1, int *fd)
{
	dup2(bkp_1, 1);
	dup2(bkp_0, 0);
	close(bkp_0);
	close(bkp_1);
	close(fd[1]);
}

void	check_the_outfile(int red_out, int *fd, char **command)
{
	if (!red_out)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	execution_first_command(command);
}

void	close_pipe_bkp(int bkp_0, int bkp_1, int *fd, int s)
{
	dup2(bkp_1, 1);
	dup2(bkp_0, 0);
	close(bkp_0);
	close(bkp_1);
	close(s);
	close(fd[0]);
	close(fd[1]);
}

void	exec_for_middle(char **command, int s, int *fd, int red_out)
{
	close(fd[0]);
	dup2(s, STDIN_FILENO);
	close(s);
	if (!red_out)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	execution_first_command(command);
}

void	check_the_infile(int red_in, int *fd, char **command, int s)
{
	if (!red_in)
	{
		close(fd[1]);
		dup2(s, STDIN_FILENO);
		close(s);
	}
	execution_first_command(command);
	exit(127);
}
