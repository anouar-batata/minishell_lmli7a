/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:21:37 by alouriga          #+#    #+#             */
/*   Updated: 2024/11/03 22:24:45 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_for_middle(int bkp_1, int bkp_0, int *fd)
{
	dup2(bkp_1, 1);
	dup2(bkp_0, 0);
	close(bkp_0);
	close(bkp_1);
	close(fd[1]);
}

void	close_for_middle_2(int bkp_1, int bkp_0, int *fd, int s)
{
	dup2(bkp_1, 1);
	dup2(bkp_0, 0);
	close(bkp_0);
	close(bkp_1);
	close(fd[1]);
	close(s);
}

void	write_error_fork(int *fd)
{
	write(2, "bash: fork: Resource temporarily unavailable\n", 46);
	exit_status(1, ADD);
	close(fd[0]);
	close(fd[1]);
}

int	execute_pipes_helper(t_commands *tmp, int *fd, int save_fd, int nb_of_nds)
{
	int	i;
	int	pid_of_last_command;

	i = 0;
	pid_of_last_command = 0;
	pipe(fd);
	nb_of_nds = ft_lstsize_2(tmp);
	if (first_execution(tmp->command, tmp, fd) == -3)
		return (write_error_fork(fd), -5);
	save_fd = fd[0];
	tmp = tmp->next;
	nb_of_nds -= 1;
	while (i < nb_of_nds - 1)
	{
		if (middle_execution(tmp->command, tmp, fd, save_fd) == -3)
			return (write_error_fork(fd), -5);
		save_fd = fd[0];
		tmp = tmp->next;
		i++;
	}
	pid_of_last_command = finale_execution(tmp->command, tmp, fd, save_fd);
	if (pid_of_last_command == -3)
		return (write_error_fork(fd), -5);
	return (pid_of_last_command);
}
