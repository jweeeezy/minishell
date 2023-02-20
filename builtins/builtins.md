-->						builtins


- all builtins are executed in the same process (even with a pipe as a last argument)

- if a command specified contains a char "/" no builtin will be executed even if the name is equal, but instead the PATH/PROGRAM will be tried to be executed

