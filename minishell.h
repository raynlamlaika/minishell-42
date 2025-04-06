#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <stdarg.h>
# include <termios.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <readline/history.h>
# include <readline/readline.h>

// representation of the deffrent type of token

typedef enum e_token_type {
    TOKEN_WORD,        // Command or argument
    TOKEN_PIPE,        // "|"
    TOKEN_REDIR_IN,    // "<"
    TOKEN_REDIR_OUT,   // ">"
    TOKEN_APPEND,      // ">>"
    TOKEN_HEREDOC,     // "<<"
    TOKEN_QUOTE,       // '"'
    TOKEN_DQUOTE,      // "'"
    TOKEN_WHITESPACE,  // " " (Should be skipped)
    TOKEN_EOF          // End of input
} t_token_type;


typedef struct s_token {
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;


typedef struct s_cmd {
	char **args;         // array of strings: command + its arguments
	char *infile;        // file for input redirection (< or <<)
	char *outfile;       // file for output redirection (> or >>)
	int append;          // 1 if >>, 0 if >
	int heredoc;         // 1 if <<, 0 if <
	struct s_cmd *next;  // pointer to the next command (if there is a pipe)
} t_cmd;


#endif