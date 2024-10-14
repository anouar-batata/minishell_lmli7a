/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:45:01 by alouriga          #+#    #+#             */
/*   Updated: 2024/10/14 19:06:48 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int   check_built_ins(char **av, t_shell *envi)
{
    if (ft_strcmp(av[0], "pwd") == 0)
	{
        pwd();
		return (0);
	}
    if (ft_strcmp(av[0], "env") == 0)
	{
        ft_env();
		return (0);
	}
    if (ft_strcmp(av[0], "echo") == 0)
	{
        echo(av);
		return (0);
	}
    if (ft_strcmp(av[0], "unset") == 0)
	{
        ft_unset(envi, av);
		return (0);
	}
    if (ft_strcmp(av[0], "export") == 0)
	{
        ft_export(av);
		return (0);
	}
    if (ft_strcmp(av[0], "cd") == 0)
	{
        if (ft_cd(av) == 2)
			return (2);
		return (0);
	}
    if (ft_strcmp(av[0], "exit") == 0)
	{
        ft_exit(av);
		return (0);
	}
	return (1);
}

void    add(char **p, t_shell **envi)
{
    int i;
    t_shell *curr;

    i = 0;
    curr = ft_lstnew(p[0], p[1]);
    ft_lstadd_back(envi, curr);
}


// int main(int ac,  char *av[], char *env[])
// {
//     // (void)
//     t_shell *envi = NULL;
//     ac = 0;
//     av = NULL;
//     int i = 0;
//     char **p;
//     while (env[i] != NULL)
//     {
//         p = split_first_equal(env[i]);
//         add(p, &envi);
//         i++;
//     }
//     env_control(0, envi, NULL);
//     while (1)
//     {
//         char *r = readline("shell:");
//         if(!r)
//             return (0);
//         add_history(r);
//         p = ft_split_2(r, ' ');
//         check_built_ins(p, envi);
//     }
    
// }
