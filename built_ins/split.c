/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:17:58 by alouriga          #+#    #+#             */
/*   Updated: 2024/08/15 05:04:06 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>
char **split_first_equal(const char *str) 
{
    char **result = malloc(3 * sizeof(char *));
    if (!result)
        return NULL;

    // Find the first '=' character
    const char *equal_pos = strchr(str, '=');
    if (!equal_pos) {
        result[0] = strdup(str);
        result[1] = NULL;
        return result;
    }

    // Allocate and copy the part before '='
    size_t key_len = equal_pos - str;
    result[0] = malloc(key_len + 1);
    if (!result[0]) {
        free(result);
        return NULL;
    }
    strncpy(result[0], str, key_len);
    result[0][key_len] = '\0';

    // Allocate and copy the part after '='
    size_t value_len = strlen(equal_pos + 1);
    result[1] = malloc(value_len + 1);
    if (!result[1]) {
        free(result[0]);
        free(result);
        return NULL;
    }
    strcpy(result[1], equal_pos + 1);

    // Null-terminate the result array
    result[2] = NULL;

    return result;
}

