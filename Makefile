# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/31 23:21:04 by alouriga          #+#    #+#              #
#    Updated: 2024/08/30 10:34:24 by alouriga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SOURCES = built_ins/cd.c built_ins/echo.c built_ins/env_utils.c \
			built_ins/env.c built_ins/exit.c built_ins/export.c \
			execution/main.c built_ins/pwd.c built_ins/split_2.c \
			built_ins/split.c built_ins/unset.c built_ins/utils.c \
			execution/utils.c built_ins/mini_main.c \
			execution/execute_pipes.c execution/exit_status_utils.c \
			
OBJ = $(SOURCES:.c=.o)
CC = cc
# CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@  -lreadline -L/Users/alouriga/.brew/opt/readline

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
