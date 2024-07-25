/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:00:54 by alouriga          #+#    #+#             */
/*   Updated: 2024/07/25 02:13:14 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
 #include <stdlib.h>
 #include <stdio.h>

typedef struct s_shell
{
    char *k;
    char *v;
    struct s_shell *next;
}   t_shell;

char	**ft_split(char const *s, char c);
t_shell	*ft_lstnew(char *k, char *v);
int ft_strlen(const char *s);
void	ft_lstadd_back(t_shell **lst, t_shell *new);
int	ft_strcmp(char *s1, char *s2);
void    pwd(t_shell *envi);
void    ft_env(t_shell *envi);
void    echo(t_shell *envi, char **av);
void    ft_exit(void);
void    ft_unset(t_shell *env, char **av);

#endif