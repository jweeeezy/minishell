# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 14:14:13 by kvebers           #+#    #+#              #
#    Updated: 2023/02/21 15:39:40 by kvebers          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CFLAGS	= -Wall -Wextra -Werror
CC		= cc
SRC	=	src/main.c src/free.c src/parse.c src/protection.c parser/tokenizer.c
RM = 	rm -f
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