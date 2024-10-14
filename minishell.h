/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:15:52 by akoutate          #+#    #+#             */
/*   Updated: 2024/10/14 15:17:57 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
#include <fcntl.h> 
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ADD_NODE 1
# define REMOVE_NODE -1
# define GET_ENV 2
# define EDIT_VALUE 3
# define ADD 1
# define GET_EXIT_STATUS 0

typedef struct redir
{
	char	*file;
	int		redir_type;
	struct redir *next;
}	t_redir;

typedef struct s_commands
{
	char 				**command;
	t_redir				*redir_lst;
	struct s_commands 	*next;
}   t_commands;


typedef struct s_memslot
{
	void				*addr;
	struct s_memslot	*next;
}				t_slot;

typedef struct s_memslotlist
{
	t_slot	*head;
	t_slot	*last;
}				t_slotlist;


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
    char *k;
    char *v;
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


int    check_the_redirection(t_commands *command);
void	ft_lstadd_back5(t_data **lst, t_data *nw);
t_data	*ft_lstnew5(char *elem, int flag);
int		ft_lstsize5(t_data *lst);
void	ft_lstiter(t_data *node);
int		ft_isalpha(int c);
void	f_list(t_data **lst);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		ft_strlen2(const char *str);
int		parse_error(t_data *lst);
char	**ft_split(char const *s, char c);
void    ft_lstadd_back2(t_shell **lst, t_shell *new);
t_shell	*ft_lstnew2(char *k, char *v);
void 	expanding(t_data *lst, t_shell *envi);
int		ft_strcmp_2(const char *s1, const char *s2);
char	*ft_strdup(char *s1);
int	    in_quote(t_data	*current_node, t_data *lst);
char	*ft_strjoin2(char *s1, char *s2);
void	join_word(t_data **lst);
void	the_other_join(t_data **lst);
char	*ft_strchr_pro(char *s, char *cc);
void	fill_lst(char *str, t_data **lst, int PIPE);
void	add_a_node(t_data **lst, char *contain, int type, int *i);
void	add_env_to_list(char *str, int *index, t_data **lst);
void	add_word_to_list(char *str, int *index, t_data **lst, int is_env);
int	    is_word(char c);
void	add_space_to_list(char *str, int *index, t_data **lst);
void    split_word(t_data	**lst);
void	make_a_list_for_louriga_aviable(t_data **lst, t_commands **command_list);
void    ft_lstadd_back3(t_commands **lst, t_commands *new);
t_commands	*ft_lstnew3(char **command, t_redir *lst);
void	ft_lstiter2(t_commands *node);
void	clean_list(t_commands **commands_list);
void    ft_lstadd_back6(t_redir **lst, t_redir *new);
t_redir	*ft_lstnew4(char *file, int flag);


int execute_programme(char **commands, char **path);
int    exit_status(int set, int mode);
void    ft_lstadd_back_2(t_commands **lst, t_commands *new);
t_commands	*ft_lstnew_2(char **command);
int    first_execution(char **command, t_commands *cmds, int *fd);
void    execute_pipes(t_commands *commands);
void    execute_command(char **command, char **path);
char *find_path(t_shell *env);
int    execute_path(char **command);
int    execution_commands(char **commands, t_commands *cmds);
void    *env_control(int behaviour, void *key, char *value);
char **split_first_equal(const char *str);
t_shell	*ft_lstnew(char *k, char *v);
void	ft_lstadd_back(t_shell **lst, t_shell *new);
void    pwd(void);
void    ft_env(void);
int    echo(char **av);
void    ft_exit(char **av);
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
char	*ft_strjoin(char *s1, char *s2);
int	ft_lstsize_2(t_commands *lst);
int	ft_strcmp(char *s1, char *s2);
size_t ft_strlen(const char *s);
int    check_built_ins(char **av, t_shell *envi);
int	ft_lstsize(t_shell *lst);
#endif
