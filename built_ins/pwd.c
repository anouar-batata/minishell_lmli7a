/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:46:37 by alouriga          #+#    #+#             */
/*   Updated: 2024/10/10 19:02:16 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void    pwd(void)
{
    char *str;

    str = getcwd(NULL, 0);
    if(!str)
    {
        perror("error\n");
        return;
    }
    printf("%s\n", str);
    free(str);
}