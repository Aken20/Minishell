	valgrind --suppressions=ignoring_readline_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes ./minishell