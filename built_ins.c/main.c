/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:45:01 by alouriga          #+#    #+#             */
/*   Updated: 2024/07/25 02:24:56 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    check_built_ins(char **av, t_shell *envi)
{
    if (ft_strcmp(av[1], "pwd") == 0)
        pwd(envi);
    if (ft_strcmp(av[1], "env") == 0)
        ft_env(envi);
    if (ft_strcmp(av[1], "echo") == 0)
        echo(envi, av);
    if (ft_strcmp(av[1], "unset") == 0)
        ft_unset(envi, av);
}

void    add(char **p, t_shell **envi)
{
    int i;
    t_shell *curr;

    i = 0;
    curr = ft_lstnew(p[0], p[1]);
    ft_lstadd_back(envi, curr);
}


int main(int ac,  char *av[], char *env[])
{
    t_shell *envi;
    int i = 0;
    char **p;
    while (env[i] != NULL)
    {
        p = ft_split(env[i], '=');
        add(p, &envi);
        i++;
    }
    check_built_ins(av, envi);
    
}