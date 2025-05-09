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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
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
	int quoted;              // 0: not quoted, 1: quoted
	struct s_token *next;
} t_token;


typedef  struct s_exp
{
	char *value;
	char **value_do;
	int flag;
	struct s_exp * next;
}					t_exp;

typedef struct s_file
{
	char *infile;
	char *outfile;
    int append;
	int here_doc;
	int flag; //check is the dilimmeter in a qoutes  double ols ingle 
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
	char **env_v;
	struct s_env *next;
} t_env;

typedef struct s_gc_collector
{
    void *ptr;
    struct s_gc_collector *next;
}t_gc_collector;

int	heredoc(char* limiter, t_env *env);

char	*get_next_line(int fd);
// char	*ft_handel_qoute(char *exp);
void    *ft_malloc(size_t size, int flag);
int	ft_isalpha(int c);
void print_env_list(t_env *head);
void	ft_exit(char **args, int exit_status);

void	handle_word(t_token **head, t_token **last, char *input, int *i);
t_token *lexer(char *input, t_token* last, int i);
void	exectution(t_cmd *full,t_env*env, int exit_s);
void	free_env_list(t_env *head);
t_env	*linked_varibles(char **env);
int ft_isdigit(int n);
void    expand(t_token *token, t_env *env);
char *ft_strjoin_free(char *s1, char *s2);
char *handling_qoutes(char *word, char sepa);
void	handle_signal(int sig);
char	*ft_strndup(char *s1, int n);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(char *str, int c);
char 	*get_value(t_env *linked_env, char *input);
void    append_token(t_token **head, t_token **last, t_token_type type, char *value);
void    handle_quotes(t_token **head, t_token **last, char *input, int *i, char quote);
int     is_redirection(t_token *tokens);
void    syntax(t_token *tokens, int *exit_s, int max_here_doc);
t_cmd	*parse_tokens(t_token *tokens, t_env *env);
char	*ft_strdup(char *s1);
int		ft_strlen(char *s1);
int		ft_strncmp(const char *str1, const char *str2, size_t num);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
char *take_replace(int i, char *input, int *help, t_env *env);
void	ft_cd(char **args);
// char *take_expand(char *input, t_env *env);
// void    ft_export(char **args, t_env *env);
int	ft_strcmp(const char *s1, const char *s2);
void	ft_unset(char **args, t_env **env);
char 	**ft_env(t_env *env);
void	ft_pwd(void);
void ft_echo(char **args, int exit_s);


#endif