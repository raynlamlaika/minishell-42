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
    char **args;             // Command and its arguments
    char *infile;            // For <
    char *outfile;           // For > or >>
    int append;              // 1 if >>, 0 if >
    int pipe_in;             // Set to 1 if receives input from previous pipe
    int pipe_out;            // Set to 1 if output is piped to next command
    struct s_cmd *next;      // For piped commands
} t_cmd;

// typedef struct s_list {
// 	char			*value;
// 	struct s_list 	*next;
// } 					t_list;

void    append_token(t_token **head, t_token **last, t_token_type type, char *value);
void    handle_quotes(t_token **head, t_token **last, char *input, int *i, char quote);
int     is_redirection(t_token *tokens);
void    syntax(t_token *tokens);
t_cmd	*parse_tokens(t_token *tokens);


#endif