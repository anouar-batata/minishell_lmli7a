/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 08:06:13 by akoutate          #+#    #+#             */
/*   Updated: 2024/08/26 23:56:42 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*ft_lstnew(char *elem, int flag)
{
	t_data	*new_node;

	new_node = malloc(sizeof(t_data));
	if (!new_node)
		return (NULL);
	new_node->elem = elem;
	new_node->flag = flag;
	new_node->to_remove = 0;
	new_node->to_split = 0;
	new_node->next = NULL;
	return (new_node);
}

t_shell	*ft_lstnew2(char *k, char *v)
{
	t_shell	*p;

	p = (t_shell *)malloc( sizeof(t_shell));
	if (!p)
		return (NULL);
	p ->name = k;
	p ->content = v;
	p ->next = NULL;
	return (p);
}