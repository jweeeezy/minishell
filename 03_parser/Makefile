# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 14:39:11 by jwillert          #+#    #+#              #
#    Updated: 2023/03/21 13:50:56 by kvebers          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	Library Name
NAME							=	parser.a

#	Directories
INCLUDE_DIR						=	../01_includes/
SRC_DIR							=	./src/
OBJ_DIR							=	./obj/

#	Libraries
LIBALLME_DIR					=	../00_liballme/
LIBFT_DIR						=	$(LIBALLME_DIR)libft/
LIBME_DIR						=	$(LIBALLME_DIR)libme/
VPATH							=	$(SRC_DIR):$(OBJ_DIR)
LIBFT							=	$(LIBFT_DIR)libft.a
LIBME							=	$(LIBME_DIR)libme.a

#	Files
SRC_FILES						=	parser.c \
									parser_utils1.c \
									parser_utils2.c \
									parser_utils3.c \
									parser_utils4.c \
									parser_utils5.c \
									parser_error1.c \
									parser_error2.c 
									
OBJ_FILES						=	$(SRC_FILES:.c=.o)
SRC								=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ								=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

#	General Rules
CC								=	cc
DEBUG							=	$(shell echo $$DEBUG_FLAG)
CFLAGS							=	-Wall -Wextra -Werror -g $(DEBUG)
INCLUDE							=	-I $(INCLUDE_DIR) -I $(LIBFT_DIR)include \
									-I $(LIBME_DIR)include
CC_OBJ							=	$(CC) $(INCLUDE) $(CFLAGS) -c $^ -o \
									$(OBJ_DIR)$@
REMOVE							=	rm -f
LIB_CREATE						=	ar -crs $(NAME)

#	Deletes target on error
.DELETE_ON_ERROR:

%.o:								%.c
										$(CC_OBJ)

#	General targets
.PHONY:								all clean fclean re
all:								$(NAME)
$(NAME):							$(LIBME) $(OBJ_FILES)
										$(LIB_CREATE) $(OBJ)
$(LIBME):
										$(MAKE) libme -C $(LIBALLME_DIR)
clean:
										$(REMOVE) $(OBJ)
fclean:								clean
										$(REMOVE) $(NAME)
re:									fclean
										$(MAKE)
