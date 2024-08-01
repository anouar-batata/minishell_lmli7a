/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 22:47:45 by alouriga          #+#    #+#             */
/*   Updated: 2024/07/31 22:49:45 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	nb_word(const char *st, char c)
{
	int	i;
	int	t;
	int	j;

	i = 0;
	t = 0;
	j = 0;
	while (st[j] != '\0')
	{
		if (st[j] != c && t == 0)
		{
			t = 1;
			i++;
		}
		else if (st[j] == c)
		{
			t = 0;
		}
		j++;
	}
	return (i);
}

static char	**free_split_memory(char **str_array, size_t j)
{
	while (j--)
	{
		free(str_array[j]);
	}
	free(str_array);
	return (NULL);
}

static	char	*dimensional(const char *s, int d, int f)
{
	int		i;
	char	*p;

	i = 0;
	p = (char *)malloc((f - d + 1) * sizeof(char));
	if (!p)
	{
		free(p);
		return (NULL);
	}
	while (d < f)
	{
		p[i] = s[d];
		i++;
		d++;
	}
	p[i] = '\0';
	return (p);
}

static char	**allocation(const char *s, size_t i, char c)
{
	int		v;
	size_t	j;
	char	**p;

	v = -1;
	j = 0;
	p = malloc((nb_word(s, c) + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && v == -1)
			v = i;
		else if ((s[i] == c || i == ft_strlen(s)) && v >= 0)
		{
			p[j] = dimensional(s, v, i);
			if (!p[j])
				return (free_split_memory(p, j));
			v = -1;
			j++;
		}
		i++;
	}
	p[j] = NULL;
	return (p);
}
char	**ft_split_2(char const *s, char c)
{
	size_t	i;
	int		v;
	size_t	j;

	v = -1;
	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	return (allocation(s, i, c));
}