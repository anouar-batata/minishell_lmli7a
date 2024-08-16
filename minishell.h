
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:00:54 by alouriga          #+#    #+#             */
/*   Updated: 2024/07/26 07:03:54 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
 #include <stdlib.h>
 #include <stdio.h>
 #include <readline/readline.h>

# define ADD_NODE 1
# define REMOVE_NODE -1
# define GET_ENV 2
# define EDIT_VALUE 3

typedef struct s_shell
{
	char *k;
	char *v;
	struct s_shell *next;
}   t_shell;

typedef struct s_input
{
	int pipe;
	char **command;
	struct s_input *next;
}   t_input;

void    *env_control(int behaviour, void *key, char *value);
char **split_first_equal(const char *str);
t_shell	*ft_lstnew(char *k, char *v);
int ft_strlen(const char *s);
void	ft_lstadd_back(t_shell **lst, t_shell *new);
int	ft_strcmp(char *s1, char *s2);
void    pwd(void);
void    ft_env(void);
int    echo(t_shell *envi, char **av);
void    ft_exit(void);
void    ft_unset(t_shell *env, char **av);
void    ft_export(char **command);
t_shell	*ft_lstlast(t_shell *lst);
void    add(char **p, t_shell **envi);
void    remove_node(t_shell **env, char *str);
void	ft_putstr(char *s);
char	**ft_split_2(char const *s, char c);
void    add_node(t_shell **env, char *k, char *v);
void    ft_cd(char **av);
void	replace_value(t_shell **env, char **arg);
char	*ft_strjoin(char const *s1, char const *s2);
#endif