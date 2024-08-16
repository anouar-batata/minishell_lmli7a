/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 09:12:19 by alouriga          #+#    #+#             */
/*   Updated: 2024/08/15 05:02:29 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_env(void)
{
    t_shell *env;

    env = env_control(2, NULL, NULL);
    while (env)
    {
        if (env->v)
            printf("%s=%s\n", env->k, env->v);
        env = env->next;
    }
}