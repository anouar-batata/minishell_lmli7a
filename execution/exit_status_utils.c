/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:14:27 by alouriga          #+#    #+#             */
/*   Updated: 2024/08/30 10:36:42 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    exit_status(int set, int mode)
{
    static int exit_status;

    // exit_status = 0;
    if (mode == ADD)
        exit_status = set;
    else
        return (exit_status);
    return(0);
}