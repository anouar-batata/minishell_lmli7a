/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_b_coll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:16:25 by alouriga          #+#    #+#             */
/*   Updated: 2024/10/14 15:17:22 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_slotlist	*start_session(void)
{
	t_slotlist	*node;

	node = malloc(sizeof(t_slotlist));
	if (node == NULL)
		return (NULL);
	node->head = NULL;
	node->last = NULL;
	return (node);
}

/*
* free everything !
* loop over all allocated addresses and free them
*/
void	close_session(t_slotlist **slots)
{
	t_slot	*head;
	t_slot	*tmp;

	head = (*slots)->head;
	while (head)
	{
		tmp = head;
		free(tmp->addr);
		free(tmp);
		head = head->next;
	}
	free(*slots);
}

/*
* alloc and store address in the list
*/
void	*ft_malloc(t_slotlist *slots, size_t size)
{
	t_slot	*new_alloc;

	new_alloc = malloc(sizeof(t_slot));
	if (!new_alloc)
		return (NULL);
	new_alloc->addr = malloc(size);
	if (!(new_alloc->addr))
	{
		close_session(&slots);
		return (NULL);
	}
	new_alloc->next = NULL;
	if (!slots->head)
	{
		slots->head = new_alloc;
		slots->last = new_alloc;
	}
	else
	{
		slots->last->next = new_alloc;
		slots->last = new_alloc;
	}
	return (new_alloc->addr);
}