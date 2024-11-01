/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:51:45 by akoutate          #+#    #+#             */
/*   Updated: 2024/10/31 17:45:46 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	the_other_join(t_data **lst)
{
	t_data	*tmp;
	t_data	*current;

	tmp = *lst;
	while (tmp)
	{
		current = tmp;
		tmp = tmp->next;
		while (tmp && current->to_remove == 0
			&& current->flag == WORD && tmp->flag == current->flag)
		{
			current->elem = ft_strjoin2(current->elem, tmp->elem);
			tmp->to_remove = 1;
			tmp = tmp->next;
		}
	}
}
