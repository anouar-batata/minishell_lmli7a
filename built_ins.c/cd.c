/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:51:43 by alouriga          #+#    #+#             */
/*   Updated: 2024/08/09 05:47:05 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// void	*add_pwd(char *key, char *value)
// {
//     int k;
//     t_shell *tmp;
// 	t_shell *env = env_control(GET_ENV, 0, 0);
// 	while (1)
// 	{
// 		tmp = env;
// 		k = 0;
// 		while (tmp && k == 0)
// 		{
// 			if (ft_strcmp(key, tmp->k) == 0)
// 			{
// 				replace_pwd(&env, value);
// 				k = 1;
// 			}
// 			tmp = tmp->next;
// 		}
// 	}
// 	return (NULL);
// }


void change_the_directory()
{
    char *str;
    char *old_pwd;
    t_shell *env;
    t_shell *tmp;

    str = getcwd(NULL, 0);
    env = env_control(GET_ENV, 0, 0);
    tmp = env;
    while (tmp)
    {
        if (ft_strcmp(tmp->k, "PWD") == 0)
        {
            old_pwd = tmp->v;
            break;   
        }
        tmp = tmp->next;
    }
    env_control(EDIT_VALUE, "PWD", str);
    env_control(EDIT_VALUE,"OLDPWD", old_pwd);
}

char    *get_home()
{
    t_shell *env;
    t_shell *tmp;

    env = env_control(GET_ENV, 0, 0);
    tmp = env;
    while (tmp)
    {
        if (!ft_strcmp(tmp->k, "HOME"))
            return (tmp->v);   
        tmp = tmp->next;
    }
    return (NULL);
}

void    ft_cd(char **av)
{
    char *str;

    if (av[1] == NULL)
        str = get_home();
    else
        str = av[1];
    if (!chdir(str))
        change_the_directory();
}