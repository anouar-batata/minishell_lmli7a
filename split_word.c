/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:53:27 by akoutate          #+#    #+#             */
/*   Updated: 2024/09/07 15:29:18 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void split_word(t_data	**lst)
{
	t_data *new_lst;
    t_data *tmp;
    t_data *tmp2;
    int     i;

    tmp = *lst;
    i = 0;
    while (tmp)
    {
        new_lst = NULL;
        if (i == 0 && tmp->to_split)
        {
            fill_lst(tmp->elem, &new_lst, 1);
            tmp2 = (*lst)->next;
            (*lst) = new_lst;
            free(tmp->elem);
            free(tmp);
            while (new_lst->next)
                new_lst = new_lst->next;
            new_lst->next = tmp2;
            tmp = (*lst);
        }
        
        else if (tmp->next && tmp->next->to_split)
        {
            fill_lst(tmp->next->elem, &new_lst, 1);    
            tmp2 = tmp->next->next;
            free(tmp->next->elem);
            free(tmp->next);
            tmp->next = new_lst;
            while (new_lst->next)
                new_lst = new_lst->next;
            new_lst->next = tmp2;
        }
        i++;
        tmp = tmp->next;
    }
}
