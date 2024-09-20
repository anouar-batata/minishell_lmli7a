/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:22:21 by codespace         #+#    #+#             */
/*   Updated: 2024/09/20 18:36:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_list(t_commands **commands_list)
{
	t_commands *tmp;

	while (*commands_list)
	{
		if ((*commands_list)->next && (*commands_list)->next->command[0] == NULL)
		{
			tmp = (*commands_list)->next;
			(*commands_list)->next = (*commands_list)->next->next;
			free(tmp);
		}
		(*commands_list) = (*commands_list)->next;
	}
}