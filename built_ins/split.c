/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:17:58 by alouriga          #+#    #+#             */
/*   Updated: 2024/11/02 15:05:42 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_strcpy(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*src)
	{
		*ptr++ = *src++;
	}
	*ptr = '\0';
	return (dest);
}

char	*my_strncpy(char *dest, const char *src, size_t n)
{
	char	*ptr;

	ptr = dest;
	while (n > 0 && *src)
	{
		*ptr++ = *src++;
		n--;
	}
	while (n > 0)
	{
		*ptr++ = '\0';
		n--;
	}
	return (dest);
}

char	*ft_strchrr(const char *s, int c)
{
	while (*s)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*(unsigned char *)s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

char	**split_first_equal(const char *str, char **result
							, const char *equal_pos, size_t key_len)
{
	size_t		value_len;

	result = smart_malloc(3 * sizeof(char *), ENVT);
	if (!result)
		exit (1);
	equal_pos = ft_strchrr(str, '=');
	if (!equal_pos)
	{
		result[0] = ft_strdup((char *)str);
		result[1] = NULL;
		return (result);
	}
	key_len = equal_pos - str;
	result[0] = smart_malloc(key_len + 1, ENVT);
	if (!result[0])
		exit (1);
	my_strncpy(result[0], str, key_len);
	result[0][key_len] = '\0';
	value_len = ft_strlen(equal_pos + 1);
	result[1] = smart_malloc(value_len + 1, ENVT);
	if (!result[1])
		exit (1);
	my_strcpy(result[1], equal_pos + 1);
	result[2] = NULL;
	return (result);
}
