/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:15:52 by akoutate          #+#    #+#             */
/*   Updated: 2024/09/02 08:22:21 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_commands
{
	char **command;
	
	struct s_commands *next;
}   t_commands;


typedef struct t_data
{
	char			*elem;
	int				flag;
	int				to_remove;
	int				to_split;	
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
int	    in_quote(t_data	*current_node, t_data *lst);
char	*ft_strjoin(char *s1, char *s2);
void	join_word(t_data **lst);
void	the_other_join(t_data **lst);
char	*ft_strchr(char *s, char *cc);
void	fill_lst(char *str, t_data **lst);
void	add_a_node(t_data **lst, char *contain, int type, int *i);
void	add_env_to_list(char *str, int *index, t_data **lst);
void	add_word_to_list(char *str, int *index, t_data **lst);
int	    is_word(char c);
void	add_space_to_list(char *str, int *index, t_data **lst);
void    split_word(t_data	**lst);
void	make_a_list_for_louriga_aviable(t_data **lst, t_commands **command_list);
void    ft_lstadd_back3(t_commands **lst, t_commands *new);
t_commands	*ft_lstnew3(char **command);
void	ft_lstiter2(t_commands *node);

#endif
