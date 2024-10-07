# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/31 23:21:04 by alouriga          #+#    #+#              #
#    Updated: 2024/10/05 14:05:12 by alouriga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SOURCES = built_ins/cd.c built_ins/echo.c built_ins/env_utils.c \
			built_ins/env.c built_ins/exit.c built_ins/export.c \
			execution/main.c built_ins/pwd.c built_ins/split_2.c \
			built_ins/split.c built_ins/unset.c built_ins/utils.c \
			execution/utils.c built_ins/mini_main.c execution/redirection.c \
			execution/execute_pipes.c execution/exit_status_utils.c \
			error_handling.c expanding.c ft_lstadd_back.c ft_lstnew.c \
			ft_lstsize.c ft_split.c ft_strjoin.c join.c louriga_aviable.c \
			minishell.c split_word.c utils.c words_join.c clean_list.c

OBJ = $(SOURCES:.c=.o)
CC = cc
# CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@ -g -lreadline 

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -g -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
