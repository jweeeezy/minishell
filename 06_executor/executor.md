-->				executor

//  What should happen beforehand?

-   Input is tokenized, so we can count how many redirections and pipes there
    will be
-   Redirections and pipes are marked by an int flag
-   Maybe we can set binary values to 1 if there is at least one of a kind
    (pipe / redirection / heredoc) == bitmask
-   Then we could write functions for setting and reading the bitmask,
    just like for signals

//  incoming struct

s_execute
    char    *order_str;
    int order_numb;

-   Executor should prob priotize Heredoc > redirections > pipes
-   Util function for setting up file descriptors for parent/child read/write


//  module flow

if heredoc == FOUND
    open heredoc (env vars, delimiter)
else
    if redirection == FOUND
        if file != FOUND
            create file
        swap fd
    if pipe == FOUND
        create pipe_fd 
