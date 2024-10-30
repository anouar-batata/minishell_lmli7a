/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:46:37 by alouriga          #+#    #+#             */
/*   Updated: 2024/10/30 15:11:08 by akoutate         ###   ########.fr       */
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
