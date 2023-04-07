//	Heredoc flow
//
//	while index < counter_heredocs
//	if heredoc
//	create heredoc node
//	open pipe
//		create child
//		open heredoc
//		find delimiter
//		write to write end of pipe
//		close pipe
//		exit
//	in parent
//	wait for child
//	READ TO BUFFER AND EXPAND BEFORE CHILD?
//	save read end for execution_child
//	EXPANSION IN CHILD?
