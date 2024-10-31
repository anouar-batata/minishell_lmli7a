/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louriga_aviable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 05:50:22 by akoutate          #+#    #+#             */
/*   Updated: 2024/10/31 15:56:00 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_dels(t_data *lst)
{
	int i;

	i = 0;
	while (1)
	{
		if (lst && lst->next && lst->next->flag == HERE_DOC)
		{
			i++;
			lst = lst->next->next;
		}	
		else
		{
			if (lst)
				i++;
			break;
		}
	}
	return (i);
}

char **add_dels(t_data **lst)
{
	char **dels;
	int	count;
	int	i;

	i = 0;
	count = count_dels(*lst);
	dels = smart_malloc ((count + 1) * sizeof(char *), RL);
	if (!dels)
		exit(1);
	dels[i] = (*lst)->elem;
	i++;
	while (1)
	{
		if (i == count)
			break;
		if (*lst && (*lst)->flag == HERE_DOC)
		{
			dels[i] = (*lst)->next->elem;
			i++;
		}
		*lst = (*lst)->next;
	}
	dels[i] = NULL;
	return (dels);
}

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
		if (lst && lst->next && (lst->flag == REDIR_IN || lst->flag == REDIR_OUT || lst->flag == DREDIR_OUT || lst->flag == HERE_DOC))
		{
			lst = lst->next->next;
			continue;
		}
		i++;
		lst = lst->next;
	}
	return (i);
}

void  make_a_list_for_louriga_aviable(t_data *lst, t_commands **command_list, t_shell *envi)
{
    t_data *tmp;
	t_redir *redir_lst = NULL;
    void *new;
    char **commands;
    int i;
    int command_count;
	
    tmp = lst;
    command_count = command_counter(tmp);
	commands = smart_malloc((command_count + 1) * sizeof(char*), RL);
    if (!commands)
        exit (1);
    i = 0;
    while (tmp)
    {
        if (tmp->flag == PIPE_LINE)
        {
            commands[i] = NULL;
            new = ft_lstnew3(commands, redir_lst);
            ft_lstadd_back3(command_list, new);
			tmp = tmp->next;
			while (tmp && tmp->flag == PIPE_LINE)
				tmp = tmp->next;
            command_count = command_counter(tmp);
			redir_lst = NULL;
            commands = smart_malloc((command_count + 1) * sizeof(char*), RL);
            if (!commands)
                exit(1);
            i = 0;
        }
        if (tmp)
		{
			if (tmp->flag == REDIR_IN || tmp->flag == REDIR_OUT || tmp->flag == DREDIR_OUT)
			{
				if (tmp->ambiguous)
					new = ft_lstnew4(NULL, tmp->flag, 0, tmp->ambiguous);
				else
				{
					new = ft_lstnew4(tmp->next->elem, tmp->flag, 0, tmp->ambiguous);
					tmp = tmp->next;
				}
				ft_lstadd_back6(&redir_lst, new);
				if (tmp)
					tmp = tmp->next;
				continue;
			}
			else if (tmp->flag == HERE_DOC)
			{
				tmp = tmp->next;
				char **dels = add_dels(&tmp);
				int to_expand;
				while (lst && lst->next && lst->next != tmp)
					lst = lst->next;
				to_expand = lst->expand_heredoc;
				new = ft_lstnew4(heredo9(dels, envi, to_expand, command_count) , REDIR_IN, 1, 0);
				ft_lstadd_back6(&redir_lst, new);
				tmp = tmp->next;
				continue;
			}
			commands[i] = tmp->elem;
        	i++;
		}
		if (tmp)
        	tmp = tmp->next;
    }
	commands[i] = NULL;
	new = ft_lstnew3(commands, redir_lst);
	ft_lstadd_back3(command_list, new);
}
