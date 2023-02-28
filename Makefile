# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 14:14:13 by kvebers           #+#    #+#              #
#    Updated: 2023/02/28 13:46:44 by kvebers          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CFLAGS	=	-Wall -Wextra -Werror -g
CC		=	cc
SRC		=	src/main.c\
			free/free.c\
			protection/protection.c\
			03_expander/env_to_list.c\
			01_lexer/lexer.c \
			01_lexer/tokenizer.c \
			utils/utils.c \
			02_parser/parser.c \
			06_builtins/echo.c
RM 		= 	rm -f
SRC_O	= $(SRC:%.c=%.o)

all:  $(NAME)

$(NAME): $(SRC_O)
	make -C ./libft
	$(CC) $(CFLAGS) $(SRC_O) libft/libft.a -o $(NAME) -lreadline

clean:
	@make clean -C libft/
	- @$(RM) $(SRC_O)

fclean: clean
	@make fclean -C libft/
	- @$(RM) ${NAME}

re: fclean all

.PHONY: clean fclean all re