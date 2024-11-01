/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:18:55 by akoutate          #+#    #+#             */
/*   Updated: 2024/10/31 18:11:42 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen2(const char *str)
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
	exit(1);
}

char	*ft_strdup(char *s1)
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

static int	numlen(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	f_str(char *str, long nbr, int len)
{
	int	dex;

	dex = len - 1;
	if (nbr == 0)
		str[0] = '0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	while (nbr != 0)
	{
		str[dex--] = (nbr % 10) + '0';
		nbr /= 10;
	}
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		len;
	char	*str;

	nbr = n;
	len = numlen(nbr);
	str = (char *)smart_malloc(sizeof(char) * (len + 1), RL);
	if (!str)
		exit(1);
	str[len] = '\0';
	f_str(str, nbr, len);
	return (str);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;

	len = ft_strlen2(src);
	i = 0;
	if (dstsize != 0)
	{
		while ((i < dstsize - 1) && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}
