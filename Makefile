# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 12:52:07 by jwillert          #+#    #+#              #
#    Updated: 2023/03/03 16:08:20 by jwillert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	Programm Name
NAME								=	minishell

#	Directories
LIBALLME_DIR						=	./00_liballme/
LIBFT_DIR							=	$(LIBALLME_DIR)/libft/
LIBME_DIR							=	$(LIBALLME_DIR)/libme/
HEADER_DIR							=	./01_includes/
LEXER_DIR							=	./02_lexer/
PARSER_DIR							=	./03_parser/
EXPANDER_DIR						=	./04_expander/
REDIRECTOR							=	./05_redirector/
EXECUTOR							=	./06_executor/
BUILTINS_DIR						=	./07_builtins/
SIGNALS_DIR							=	./08_signals/
CORE_DIR							=	./09_core/
DEBUG_DIR							=	./10_debug/
MODULES_DIR_ALL						=	$(LEXER_DIR)\
										$(PARSER_DIR)\
										$(BUILTINS_DIR)\
										$(CORE_DIR)\
										$(EXPANDER_DIR)\
										$(DEBUG_DIR)
										#$(REDIRECTOR_DIR)\#
										#$(EXECUTOR_DIR)\#
										#$(SIGNALS_DIR)#

#	Libraries
LIBME								=	$(LIBME_DIR)libme.a
LEXER								=	$(LEXER_DIR)lexer.a
PARSER								=	$(PARSER_DIR)parser.a
EXPANDER							=	$(EXPANDER_DIR)expander.a
REDIRECTOR							=	$(REDIRECTOR_DIR)redirector.a
EXECUTOR							=	$(EXECUTOR_DIR)executor.a
BUILTINS							=	$(BUILTINS_DIR)builtins.a
SIGNALS								=	$(SIGNALS_DIR)signals.a
CORE								=	$(CORE_DIR)core.a
DEBUG								=	$(DEBUG_DIR)debug.a
MODULES_ALL							=	$(LIBME)\
										$(LEXER)\
										$(PARSER)\
										$(BUILTINS)\
										$(CORE)\
										$(EXPANDER)\
										$(DEBUG)
										#$(REDIRECTOR)\#
										#$(EXECUTOR)\#
										#$(SIGNALS)#

#	General Rules
CC									=	cc
CC_DEBUG							=	$(shell $$DEBUG_FLAG)
CFLAGS								=	-Wall -Wextra -Werror $(CC_DEBUG) \
										-lreadline
REMOVE								=	rm -f

#	Deletes targets on error
.DELETE_ON_ERROR:

#	General targets
.PHONY:									all clean fclean re
all:									$(NAME)
$(NAME):								$(MODULES_ALL)
											$(CC) $(CFLAGS) $(MODULES_ALL) \
												-o $(NAME)
$(MODULES_ALL):
											$(MAKE) libme -C $(LIBALLME_DIR)
											for dir in $(MODULES_DIR_ALL); do\
												$(MAKE) -C $$dir; \
											done
clean:
											$(MAKE) clean -C $(LIBALLME_DIR)
											for dir in $(MODULES_DIR_ALL); do\
												$(MAKE) clean -C $$dir; \
											done
fclean:									clean
											$(MAKE) fclean -C $(LIBALLME_DIR)
											for dir in $(MODULES_DIR_ALL); do\
												$(MAKE) fclean -C $$dir; \
											done
											$(REMOVE) $(NAME)
re:										fclean
											$(MAKE)
