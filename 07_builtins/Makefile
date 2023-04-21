# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 15:18:22 by jwillert          #+#    #+#              #
#    Updated: 2023/04/21 16:56:03 by kvebers          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	Library Name
NAME							=	builtins.a

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
SRC_FILES						=	builtin_pwd.c\
									builtin_env.c\
									builtin_echo.c\
									builtin_utils.c\
									builtin_exit.c\
									builtin_unset.c\
									builtin_export.c\
									builtin_errors_flags.c\
									builtin_cd.c
OBJ_FILES						=	$(SRC_FILES:.c=.o)
SRC								=	$(addprefix $(SRC_DIR),$(SRC_FILES))
OBJ								=	$(addprefix $(OBJ_DIR),$(OBJ_FILES))

#	General rules
CC								=	cc
DEBUG							=	$(shell echo $$DEBUG_FLAG)
CFLAGS							=	-Wall -Wextra -Werror $(DEBUG)
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
										$(REMOVE) a.out
re:									fclean
										$(MAKE)
