/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:51:45 by akoutate          #+#    #+#             */
/*   Updated: 2024/08/17 17:53:39 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	the_other_join(t_data **lst)
{
	t_data *tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->next && tmp->flag == WORD && tmp->next->flag == WORD)
		{
			
		}
		tmp = tmp->next;
	}
}
