#!/usr/bin/env bash

#	Lets lldb wait for a process called minishell and then setting up a
#	breakpoint before continuing the process

lldb -s <(echo "process attach -name minishell --waitfor") \
-o "process continue"

#-o "b executor" \
