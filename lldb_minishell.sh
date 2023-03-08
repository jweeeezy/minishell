# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    lldb_minishell.sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 13:39:42 by jwillert          #+#    #+#              #
#    Updated: 2023/03/02 09:06:36 by jwillert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#!/usr/bin/env bash

#	Lets lldb wait for a process called minishel and then setting up a breakpoint
#	before continuing the process

lldb -s <(echo "process attach -name minishell --waitfor") \
-o "b executor_main" \
-o "process continue"

