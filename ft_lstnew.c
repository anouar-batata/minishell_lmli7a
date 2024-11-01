/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 08:06:13 by akoutate          #+#    #+#             */
/*   Updated: 2024/11/01 06:28:03 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*ft_lstnew5(char *elem, int flag)
{
	t_data	*new_node;

	new_node = smart_malloc(sizeof(t_data), RL);
	if (!new_node)
		exit (1);
	new_node->elem = elem;
	new_node->flag = flag;
	new_node->to_remove = 0;
	new_node->to_split = 0;
	new_node->expand_heredoc = 1;
	new_node->ambiguous = 0;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

t_shell	*ft_lstnew2(char *k, char *v)
{
	t_shell	*p;

	p = smart_malloc(sizeof(t_shell), ENVT);
	if (!p)
		exit(1);
	p ->k = k;
	p ->v = v;
	p ->next = NULL;
	return (p);
}

t_commands	*ft_lstnew3(char **command, t_redir *lst)
{
	t_commands	*new;

	new = smart_malloc(sizeof(t_commands), RL);
	if (!new)
		exit(1);
	new->command = command;
	new->redir_lst = lst;
	new->next = NULL;
	return (new);
}

t_redir	*ft_lstnew4(char *file, int flag, int to_close, int ambiguous)
{
	t_redir	*new;

	new = smart_malloc(sizeof(t_redir), RL);
	if (!new)
		exit (1);
	new->file = file;
	new->redir_type = flag;
	new->to_close = to_close;
	new->ambiguous = ambiguous;
	new->next = NULL;
	return (new);
}

t_node	*ft_lstnew8(void *ptr_to_store)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		exit (1);
	new_node->ptr = ptr_to_store;
	new_node->next = NULL;
	return (new_node);
}