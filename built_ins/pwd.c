/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:46:37 by alouriga          #+#    #+#             */
/*   Updated: 2024/09/09 05:39:00 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void    pwd(void)
{
    char *str;

    str = getcwd(NULL, 0);
    if(!str)
        exit(1);
    printf("%s\n", str);
    printf("mok\n");
    free(str);
}