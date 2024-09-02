/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:18:55 by akoutate          #+#    #+#             */
/*   Updated: 2024/08/27 00:22:35 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

void	f_list(t_data **lst)
{
	write(2, "Failed to create a new list!", 28);
	ft_lstiter(*lst);
	exit(1);
}

char	*ft_strdup(char *s1)
{
	char	*cpy;
	size_t	i;

	cpy = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
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
	s_len = ft_strlen(s);
	i = 0;
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	tmp = (char *)malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	while ((i < len) && s[start + i])
	{
		tmp[i] = s[start + i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	ft_strcmp(const char *s1, const char *s2)
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

char	*ft_strchr(char *s, char *cc)
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
		if (* cc == '\0')
			return ((char *)&s[i]);
		cc++;
	}
	return (NULL);
}