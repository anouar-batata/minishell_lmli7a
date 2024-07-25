/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:53:55 by alouriga          #+#    #+#             */
/*   Updated: 2024/07/25 02:18:45 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    remove_node(t_shell **env, char *str)
{
    t_shell *tmp = *env;
    t_shell *prev = NULL;

    if (tmp != NULL && ft_strcmp(tmp->k, str) == 0)
    {
        *env = tmp->next;
        free(tmp->k);
        free(tmp->v);
        free(tmp);
        return ;
    }
    while (tmp && ft_strcmp(tmp->k, str) != 0)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
     prev->next = tmp->next;
     free(tmp->k);
     free(tmp->v);
}

void    ft_unset(t_shell *env, char **av)
{
    int i;

    i = 0;
    t_shell *curr;
    curr = env;
    while (curr)
    {
        if (ft_strcmp(av[2], curr->k) == 0)
        {
            remove_node(&env, curr->k);
            ft_env(env);
            return ;
        }
        curr = curr->next;
        
    }
    
}