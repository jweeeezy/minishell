#!/usr/bin/env bash

#	Lets lldb wait for a process called minishell and then setting up a
#	breakpoint before continuing the process

lldb -s <(echo "process attach -name minishell --waitfor") \
-o "b executor_pipex" \
-o "process continue"

