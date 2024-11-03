/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 06:31:27 by akoutate          #+#    #+#             */
/*   Updated: 2024/11/01 16:56:56 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back8(t_node **lst, t_node *new)
{
	t_node	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	*globalizer_head(int mode, void *ptr, int type)
{
	static t_node	*rl_lst;
	static t_node	*env_lst;

	if (mode == 1)
	{
		if (type == RL)
			rl_lst = ptr;
		else
			env_lst = ptr;
		return (NULL);
	}
	else
	{
		if (type == RL)
			return (rl_lst);
		else
			return (env_lst);
	}
}

int	store_smart_mallocs(void *ptr_to_add, int type)
{
	t_node	*head;
	t_node	*new_node;

	head = globalizer_head(0, NULL, type);
	new_node = ft_lstnew8(ptr_to_add);
	if (!new_node)
	{
		exit(1);
	}
	if (!head)
		globalizer_head(1, new_node, type);
	else
		ft_lstadd_back8(&head, new_node);
	return (1);
}

void	*smart_malloc(size_t size, int type)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr && store_smart_mallocs(ptr, type))
		return (ptr);
	return (NULL);
}

void	smart_free(int type)
{
	t_node	*current;
	t_node	*next;

	current = globalizer_head(0, NULL, type);
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	globalizer_head(1, NULL, type);
	
}
