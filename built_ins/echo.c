/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 09:19:30 by alouriga          #+#    #+#             */
/*   Updated: 2024/09/29 16:51:17 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int  check_the_option(char **av)
{
    int i = 0;
    int j = 0;
    int k = 1;

    j = 1;
    while (av[i])
    {
        k = 1;
        j = 0;
        while (av[i][j] && av[i][0] == '-')
        {
            if (ft_strlen(av[i]) == 1)
                break;
            if (av[i][j] == 'n')
                k++;
            j++;
        }
        if (k == j)
        {
            // printf("%d\n", j);
            // printf("%d\n", k);
            i++;
        }
        else
        {
            // i = i + 1;
            while (av[i])
            {
                ft_putstr(av[i]);
                if (av[i + 1] != NULL)
                write(1, " ", 1);
                i++;
            }
            return (0);
        }
    }
    return (1);
}

int    echo(char **av)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (av[++i])
    {
        if (av[i][j] == '-')
        {
            if (!check_the_option(&av[i]))
                return (1);
        }
        ft_putstr(av[i]);
        if (av[i + 1] != NULL)
            write(1, " ", 1);
    }
    printf("\n");
    return (0);
}