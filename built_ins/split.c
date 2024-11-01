/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:17:58 by alouriga          #+#    #+#             */
/*   Updated: 2024/11/01 06:09:39 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>
char **split_first_equal(const char *str) 
{
    char **result = smart_malloc(3 * sizeof(char *), ENVT);
    if (!result)
        exit(1);

    // Find the first '=' character
    const char *equal_pos = strchr(str, '=');
    if (!equal_pos) {
        result[0] = ft_strdup((char *)str);
        result[1] = NULL;
        return result;
    }

    // Allocate and copy the part before '='
    size_t key_len = equal_pos - str;
    result[0] = smart_malloc(key_len + 1, ENVT);
    if (!result[0]) {
        exit (1);
    }
    strncpy(result[0], str, key_len);
    result[0][key_len] = '\0';

    // Allocate and copy the part after '='
    size_t value_len = strlen(equal_pos + 1);
    result[1] = smart_malloc(value_len + 1, ENVT);
    if (!result[1]) {
        exit (1);
    }
    strcpy(result[1], equal_pos + 1);

    // Null-terminate the result array
    result[2] = NULL;

    return result;
}

