/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louriga_aviable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 05:50:22 by akoutate          #+#    #+#             */
/*   Updated: 2024/09/02 08:51:18 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pip_counter(t_data *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->flag == PIPE_LINE)
			i++;
	}
	return (i + 1);
}

int command_counter(t_data *lst)
{
	int i;

	i = 0;
	while (lst && lst->flag != PIPE_LINE)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void make_a_list_for_louriga_aviable(t_data **lst, t_commands **command_list)
{
    t_data *tmp;
	
    t_commands *new;
    char **commands;
    int i;
    int command_count;

    tmp = *lst;
    command_count = command_counter(tmp);
    commands = malloc((command_count + 1) * sizeof(char*));
    if (!commands)
        return;
    i = 0;
    while (tmp)
    {
        if (tmp->flag == PIPE_LINE)
        {
            commands[i] = NULL;
            new = ft_lstnew3(commands);
            ft_lstadd_back3(command_list, new);
			tmp = tmp->next;
            command_count = command_counter(tmp);
            commands = malloc((command_count + 1) * sizeof(char*));
            if (!commands)
                return;
            i = 0;
        }
        
        commands[i] = tmp->elem;
        i++;
        tmp = tmp->next;
    }
    if (i > 0)
    {
        commands[i] = NULL;
        new = ft_lstnew3(commands);
        ft_lstadd_back3(command_list, new);
    }
    else
        free(commands);
}
