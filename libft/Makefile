# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 12:50:10 by kvebers           #+#    #+#              #
#    Updated: 2022/12/10 10:40:59 by kvebers          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	ft_isalnum.c ft_isprint.c ft_isdigit.c ft_atoi.c ft_bzero.c \
		ft_isalpha.c ft_calloc.c ft_isalpha.c ft_isascii.c ft_isprint.c \
		ft_itoa.c ft_strdup.c ft_memchr.c ft_memcmp.c ft_strlen.c \
		ft_toupper.c ft_tolower.c ft_strchr.c ft_memcpy.c ft_strrchr.c \
		ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_memset.c \
		ft_memmove.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
		ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_striteri.c ft_lstnew.c ft_lstadd_front.c \
		ft_lstsize.c ft_lstadd_back.c ft_lstlast.c ft_lstdelone.c \
		ft_lstiter.c ft_lstclear.c ft_lstmap.c ft_printf.c ft_putchar.c \
		ft_putdeca.c ft_puthex.c ft_putptr.c ft_putstr.c ft_putunsigned.c \
		get_next_line.c get_next_line_utils.c
CC = 		gcc
CFLAG =		-Wall	 -Wextra	 -Werror
RM = 		rm -f
NAME = 		libft.a
OBJ	= $(SRC:.c=.o)
OBJ_BONUS = $(BONUS:.c=.o)

$(NAME): $(OBJ)
	@$(AR) -rcs $@ $^

bonus: $(OBJ_BONUS)
	@$(AR) -rcs $(NAME) $^

%.o : %.c
	@$(CC) -c $(CFLAG) $< -o $@

clean:
	- @$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	- @$(RM) ${NAME}

re: fclean all

all: $(NAME) bonus

.PHONY: all clean fclean re bonus