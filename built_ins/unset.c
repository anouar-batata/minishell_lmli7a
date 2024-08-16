/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:53:55 by alouriga          #+#    #+#             */
/*   Updated: 2024/08/15 05:03:28 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void    ft_unset(t_shell *env, char **av)
{
    int i;

    i = 0;
    t_shell *curr;
    curr = env;
    while (curr)
    {
        if (ft_strcmp(av[1], curr->k) == 0)
        {
            env_control(-1, curr->k, NULL);
            return ;
        }
        curr = curr->next;
    }
}