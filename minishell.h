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

typedef enum e_token_type
{
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


typedef struct s_token
{
	t_token_type type;
	char *value;
	struct s_token *next;
} t_token;

typedef struct s_file
{
	char *infile;
	char *outfile;
    int append;
	struct s_file 	*next;
} 					t_file;


typedef struct s_cmd
{
    char **args;
    struct s_cmd *next;
	t_file *file;
} t_cmd;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

void	handle_word(t_token **head, t_token **last, char *input, int *i);
t_token *lexer(char *input, t_token* last, int i);
void	exectution(t_cmd *full,t_env*env);
void	free_env_list(t_env *head);
t_env	*linked_varibles(char **env);


void print_cmds(t_cmd *cmd);

char	*ft_strndup(char *s1, int n);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(char *str, int c);
char 	*get_value(t_env *linked_env, char *input);
void    append_token(t_token **head, t_token **last, t_token_type type, char *value);
void    handle_quotes(t_token **head, t_token **last, char *input, int *i, char quote);
int     is_redirection(t_token *tokens);
void    syntax(t_token *tokens);
t_cmd	*parse_tokens(t_token *tokens);
char	*ft_strdup(char *s1);
int		ft_strlen(char *s1);
int		ft_strncmp(const char *str1, const char *str2, size_t num);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);



#endif