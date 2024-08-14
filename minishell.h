/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:15:52 by akoutate          #+#    #+#             */
/*   Updated: 2024/08/07 05:06:22 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct t_data
{
	char			*elem;
	int				flag;
	struct t_data	*next;
}	t_data;

typedef struct s_shell
{
    char *name;
    char *content;
    struct s_shell *next;
}   t_shell;

enum e_token
{
	WORD = -1,
	WHITE_SPACE = ' ',
	QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC = -2,
	DREDIR_OUT = -3,
};

void	ft_lstadd_back(t_data **lst, t_data *nw);
t_data	*ft_lstnew(char *elem, int flag);
int		ft_lstsize(t_data *lst);
void	ft_lstiter(t_data *node);
int		ft_isalpha(int c);
void	f_list(t_data **lst);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		ft_strlen(const char *str);
int		parse_error(t_data *lst);
char	**ft_split(char const *s, char c);
void    ft_lstadd_back2(t_shell **lst, t_shell *new);
t_shell	*ft_lstnew2(char *k, char *v);
void 	expanding(t_data *lst, t_shell *envi);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(char *s1);
int	in_quote(t_data	*current_node, t_data *lst);
char	*ft_strjoin(char *s1, char *s2);
void	join_word(t_data *lst);

#endif
