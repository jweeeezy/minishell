# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/12 20:31:50 by jwillert          #+#    #+#              #
#    Updated: 2023/03/26 16:24:46 by jwillert         ###   ########           #
#                                                                              #
# **************************************************************************** #

#	Library Name
NAME							=	executor.a

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
SRC_FILES						=	executor_builtin.c\
									executor_extern.c\
									executor_extern_child.c\
									executor_extern_parent.c\
									executor_main.c\
									executor_pipex.c\
									executor_utils_count.c\
									executor_utils_is.c
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
re:									fclean
										$(MAKE)
