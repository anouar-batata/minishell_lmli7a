/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:53:55 by alouriga          #+#    #+#             */
/*   Updated: 2024/10/30 15:01:16 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int    ft_unset(t_shell *env, char **av)
{
    int i;
    int j;

    i = 1;
    j = 0;
    t_shell *curr;
    curr = env;
    while (av[i] != NULL)
    {
        j = 0;
        while (av[i][j] != '\0')
        {
            if (!((av[i][j] >= 'A' && av[i][j] <= 'Z') || (av[i][j]) == '_' || (av[i][j] >= 'a' && av[i][j] <= 'z')) && j == 0)
                    return (manage_error(av[i]) ,1);
            if (!((av[i][j] >= 'A' && av[i][j] <= 'Z') || (av[i][j] >= 'a' && av[i][j] <= 'z')|| (av[i][j]) == '_' || (av[i][j] >= '0' && av[i][j] <= '9')))
                {
                        manage_error(av[i]);
                        return (1);
                }
            j++;
        }
        i++;
    }
    i = 2;
    j = 1;
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
    return (0);
}
