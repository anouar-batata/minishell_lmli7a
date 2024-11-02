/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louriga_aviable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 05:50:22 by akoutate          #+#    #+#             */
/*   Updated: 2024/11/02 09:08:59 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redir(t_data **tmp, t_redir**redir_lst)
{
	t_redir	*new;

	if ((*tmp)->ambiguous)
		new = ft_lstnew4(NULL, (*tmp)->flag, 0, (*tmp)->ambiguous);
	else
	{
		new = ft_lstnew4((*tmp)->next->elem,
				(*tmp)->flag, 0, (*tmp)->ambiguous);
		*tmp = (*tmp)->next;
	}
	ft_lstadd_back6(redir_lst, new);
	if (*tmp)
		*tmp = (*tmp)->next;
}

void	add_heredoc(t_data **tmp, t_shell *envi,
	t_redir **redir_list, t_data **lst)
{
	char	**dels;
	int		to_expand;
	t_redir	*new;

	(*tmp) = (*tmp)->next;
	dels = add_dels(tmp);
	while (*lst && (*lst)->next && (*lst)->next != (*tmp))
		(*lst) = (*lst)->next;
	to_expand = (*lst)->expand_heredoc;
	new = ft_lstnew4(heredo9(dels, envi,
				to_expand), REDIR_IN, 1, 0);
	ft_lstadd_back6(redir_list, new);
	(*tmp) = (*tmp)->next;
}

void	func1(t_list *data, t_data **tmp, t_shell *envi, t_data **lst)
{
	if (*tmp)
	{
		if ((*tmp)->flag == REDIR_IN || (*tmp)->flag == REDIR_OUT
			|| (*tmp)->flag == DREDIR_OUT)
		{
			add_redir(tmp, &data->redir_lst);
			return ;
		}
		else if ((*tmp)->flag == HERE_DOC)
		{
			add_heredoc(tmp, envi, &data->redir_lst, lst);
			return ;
		}
		data->commands[data->i] = (*tmp)->elem;
		data->i++;
	}
	if ((*tmp))
		(*tmp) = (*tmp)->next;
}

void	func3(t_list *data, t_data **tmp, t_commands **command_list)
{
	t_commands	*new;

	data->commands[data->i] = NULL;
	new = ft_lstnew3(data->commands, data->redir_lst);
	ft_lstadd_back3(command_list, new);
	(*tmp) = (*tmp)->next;
	while ((*tmp) && (*tmp)->flag == PIPE_LINE)
		(*tmp) = (*tmp)->next;
	data->command_count = command_counter((*tmp));
	data->redir_lst = NULL;
	data->commands = smart_malloc((data->command_count + 1)
			* sizeof(char *), RL);
	if (!data->commands)
		exit(1);
	data->i = 0;
}

void	make_a_list_for_louriga_aviable(t_data *lst,
	t_commands **command_list, t_shell *envi)
{
	t_data	*tmp;
	t_redir	*redir_lst;
	void	*new;
	t_list	data;

	tmp = lst;
	data.redir_lst = NULL;
	data.command_count = command_counter(tmp);
	data.commands = smart_malloc((data.command_count + 1) * sizeof(char *), RL);
	if (!data.commands)
		exit (1);
	data.i = 0;
	while (tmp)
	{
		if (tmp->flag == PIPE_LINE)
			func3(&data, &tmp, command_list);
		func1(&data, &tmp, envi, &lst);
	}
	data.commands[data.i] = NULL;
	new = ft_lstnew3(data.commands, data.redir_lst);
	ft_lstadd_back3(command_list, new);
}
