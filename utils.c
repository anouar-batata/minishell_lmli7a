/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:18:55 by akoutate          #+#    #+#             */
/*   Updated: 2024/11/01 10:49:42 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup2(char *s1)
{
	char	*cpy;
	size_t	i;

	if (!s1)
		return (NULL);
	cpy = (char *)smart_malloc((ft_strlen2(s1) + 1) * sizeof(char), RL);
	if (!cpy)
		exit(1);
	i = 0;
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*tmp;
	size_t	s_len;

	if (!s)
		return (NULL);
	if (len == 0)
		return (ft_strdup(""));
	s_len = ft_strlen2(s);
	i = 0;
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	tmp = (char *)smart_malloc((len + 1) * sizeof(char), RL);
	if (!tmp)
		exit (1);
	while (i < len && s[start + i])
	{
		tmp[i] = s[start + i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	ft_strcmp_2(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	i = 0;
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while (ss1[i] || ss2[i])
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	return (0);
}

char	*ft_strchr_pro(char *s, char *cc)
{
	size_t			i;

	i = 0;
	while (*cc)
	{
		while (s[i])
		{
			if (s[i] == *cc)
				return ((char *)&s[i]);
			i++;
		}
		if (*cc == '\0')
			return ((char *)&s[i]);
		cc++;
	}
	return (NULL);
}
