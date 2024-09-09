/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:53:55 by alouriga          #+#    #+#             */
/*   Updated: 2024/09/04 20:13:18 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void    ft_unset(t_shell *env, char **av)
{
    int i;
    int j;

    i = 2;
    j = 1;
    t_shell *curr;
    curr = env;
    while (curr && av[j])
    {
        i = 2;
        if (ft_strcmp(av[j], curr->k) == 0)
        {
            if (!ft_strcmp(curr->k, "_"))
                i++;
            else
            {
                env_control(-1, curr->k, NULL);
                j++;
                i = 0;
            }
        }
        if (i == 0)
            curr = env;
        else
            curr = curr->next;
    }
}