# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/31 23:21:04 by alouriga          #+#    #+#              #
#    Updated: 2024/11/03 22:41:38 by alouriga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SOURCES = built_ins/cd.c built_ins/echo.c built_ins/env_utils.c built_ins/parce_export.c\
			built_ins/env.c built_ins/exit.c built_ins/export.c built_ins/utils2.c \
			execution/main.c built_ins/pwd.c built_ins/split_2.c built_ins/utils_export.c\
			built_ins/split.c built_ins/unset.c built_ins/utils.c built_ins/utils3.c \
			execution/utils.c built_ins/mini_main.c execution/redirection.c \
			execution/execute_pipes_2.c execution/execute_pipes_3.c execution/helper1.c \
			execution/execute_pipes.c execution/exit_status_utils.c execution/helper2.c \
			error_handling.c expanding.c ft_lstadd_back.c ft_lstnew.c execution/redirection2.c\
			 ft_split.c ft_strjoin.c join.c louriga_aviable.c execution/execute_pipes_4.c \
			minishell.c split_word.c utils.c words_join.c  checkers.c\
			heredo9.c garbage_collector.c deleters.c parse_funcs.c 

LINKREADLINELIB = $(shell brew --prefix readline)/lib
LINKREADLINEINCLUDE = $(shell brew --prefix readline)/include
RL_FLAGS = -I$(LINKREADLINEINCLUDE) -L$(LINKREADLINELIB)
CFLAGS = -I$(LINKREADLINEINCLUDE)
LDFLAGS = -L$(LINKREADLINELIB) -lreadline

OBJ = $(SOURCES:.c=.o)
CC = cc -g

# CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@ -g -lreadline 

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -g -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
