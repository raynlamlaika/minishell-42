/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:19:42 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/02 08:24:02 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
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

# ifndef PATH
#  define PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/\
bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"
# endif

extern int g_here_doc_helper;

typedef struct s_export
{
	char	**args;
	char	*key;
	char	*value;
	int		flag;
	int		tow_values;
}			t_export;

typedef struct s_split
{
	char	*str;
	int		i;
	int		n;
	int		m;
	int		y;
	int		a;
	int		size;
	int		add;
	char	*embg;
}			t_split;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_QUOTE,
	TOKEN_DQUOTE,
	TOKEN_WHITESPACE,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	char			*ambiguous;
	int				quoted;
	int				rm_node;
	int				flag_mbg;
	int				hlep;
	struct s_token	*next;
}					t_token;

typedef struct s_exp
{
	char			*value;
	char			**value_do;
	int				flag;
	struct s_exp	*next;
}					t_exp;

typedef struct s_file
{
	char			*infile;
	char			*outfile;
	int				append;
	int				here_doc;
	int				flag;
	struct s_file	*next;
}					t_file;

typedef struct s_cmd
{
	char			**args;
	struct s_cmd	*next;
	int				*exit_s;
	t_file			*file;
}					t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				emg_flag;
	char			**env_v;
	int				*exit_s;
	char			*pwd_d;
	struct s_env	*next;
}					t_env;

typedef struct s_malloc
{
	void			*toalloc;
	struct s_malloc	*next;
}					t_malloc;

typedef struct s_finishd
{
	int		inf;
	int		outf;
	char	**args;
	int		status;
	char	*bin;
	t_cmd	*cmd;
	t_env	*env;
}			t_finished;

typedef struct s_all_data
{
	t_cmd	*cmd;
	t_file	*file;
	t_file	*last_file;
	t_cmd	*start;
}			t_all_data;

typedef struct s_exec
{
	int		pipefd[2];
	char	**path;
	int		inf;
	int		outf;
	int		count;
}			t_exec;

typedef struct s_takes
{
	t_env	*env_list;
	t_token	*tokens;
	char	*line;
}			t_takes;

typedef struct s_expand_state
{
	int		i;
	int		a;
	t_env	*env;
	int		*exit_s;
}			t_expand_state;

typedef struct s_context
{
	t_env	**env;
	int		*exit_s;
	t_exec	*exec;
	int		perv_pipe;
}		t_context;

typedef struct s_expans
{
	char	*result;
	char	*tmp;
	int		i;
	int		quote;
	int		a;
	int		size;
	int		t;
}			t_expans;

int		*exit_status(int more, int value);
void	disconnect_flagged_nodes(t_token **head);
void	check_line_null(int*exit_s, char*line);
char	*take_replace(int i, char *input, int *help, t_env *env);
void	expand_exits_s(int *exit_s, char *result, int *a, int *i);
char	*expaned_ed(char*string, t_env *env, int i);
char	*add_quotessss( char *input);
void	initialize_helper(t_finished *helper, t_cmd *cmd, t_env **env);
void	buitin(t_finished	*helper, int *exit_s);
void	close_inf_out(t_finished	*helper, t_cmd *cmd);
void	execute_single_cmd(t_cmd *cmd, t_env **env, int *exit_s);
void	path_null(char*arg);
void	null_cmd(char*arg);
void	ft_exec(char *pathh, t_env **env, char	**cmd);
void	take_child(t_cmd *full, char **path, int *exit_s, t_env **env);
void	save_exit_s(int count, int *exit_s);
void	execute_child_process(t_cmd *full, t_context *ctx);
int		helper_s(t_finished *helper);
void	null_arg(void);
void	execute_command_s(t_finished *helper, int *exit_s);
void	handle_redirections(int inf, int outf);
int		putstr(char *string);
char	*hendel_qoutes(char *str);
int		pipecheck(int *pipefd);
char	*ft_itoa(int n);
int		synx_ambg(t_token *tokens, int *exit_s);
char	**takepaths(t_env **env);
char	*pick(char**path, char*cmd);
char	*expnd_cd(char *input, t_env *env);
int		heredoc(char*limiter, t_env *env, t_file *file);
void	ft_export(char **args, t_env **env);
void	*ft_malloc(unsigned int size, int flag);
void	get_redirections(int*inf, int *outf, t_cmd*full);
int		forkfaild(pid_t pid, int*pipefd);
int		ft_isalpha(int c);
void	ft_exit(char **args, int exit_status);
char	*ft_handel_qoute(char *exp);
void	handle_word(t_token **head, t_token **last, char *input, int*i);
t_token	*lexer(char *input, t_token*last, int i);
void	exectution(t_cmd *full, t_env**env, int*exit_s);
void	free_env_list(t_env *head);
t_env	*linked_varibles(char **env);
int		ft_isdigit(int n);
int		expand(t_token *token, t_env *env, int *exit_s);
char	*handling_qoutes(char *word, char sepa);
void	handle_signal(int sig);
char	*ft_strndup(char *s1, int n);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(char *str, int c);
char	*get_value(t_env *linked_env, char *input);
void	append_token(t_token **head, t_token **\
last, t_token_type type, char *value);
void	handle_quotes(t_token **head, t_token **last, char *input, int *i);
int		is_redirection(t_token *tokens);
int		syntax(t_token *tokens, int *exit_s, int max_here_doc);
t_cmd	*parse_tokens(t_token *tokens, t_env *env);
char	*ft_strdup(char *s1);
int		ft_strlen(char *s1);
int		ft_strncmp(const char *str1, const char *str2, size_t num);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*take_replace(int i, char *input, int *help, t_env *env);
void	ft_cd(char **args, t_env*env);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_unset(char **args, t_env **env);
void	ft_env(t_env *env);
void	ft_pwd(t_env *env);
void	ft_echo(char **args, int exit_s);
t_env	*null_helper(t_env *head);
t_env	*new_node(char *key, char *value);
int		size_help(char *string, t_env *env, int *exit_s);
char	*ft_take(char*string, int *i, t_env *env);
char	*s_split(char *result, t_token *token, char *embg);
void	replace_token(char **token_value, char *exp);
char	*ft_take(char*string, int *i, t_env *env);
int		ft_isalnum(int c);
char	*ft_replace(char *check, t_env *env);
t_token	*create_token(char *value, char *help_red);
void	insert_token_after(t_token *current, t_token *new_token);
void	ft_free(t_malloc **head);
void	handelprevpipe(int *pipefd, int *prev_pipe);
int		is_passed(char *str, char *sec);
int		search_search(char *str);
void	buildin(t_cmd *cmd, t_env **env, int *exit_s);
char	*take_key(char **env, int i, int j);
char	*take_value(char **env, int i, int j);
t_env	*new_node(char *key, char *value);
int		append_node(t_env **head, t_env *new);
t_env	*linked_varibles(char **env);
char	*take_token(char *string, t_env *env, int*exit_s);
void	add_arg(t_cmd *type, char *value);
void	token_infile(t_file **last_file, t_file *file, t_token *tokens);
void	token_outfile(t_file **last_file, t_file *file, t_token *tokens);
void	token_append(t_file **last_file, t_file *file, t_token *tokens);
void	token_heredoc(t_file **last_file, t_file *file, \
	t_token *tokens, t_env *env);
void	*ft_calloc(size_t count, size_t size);
int		is_valid_varname(char *name);
void	add_to_env_list(t_env **env_list, t_env *new_node);
void	ft_print_env(t_env *env);
int		ft_isdigit(int c);
char	*take_key_exp(char*str, int j);
int		f_size(char *str, int i);
char	*takee_value(char *str, int pointed_to);
t_env	*search_node(char *key, t_env *head);
int		check_empty(char **args, int *i, int *j);
void	execute_command_s(t_finished *helper, int *exit_s);
void	handle_redirections(int inf, int outf);
void	execute_forked_cmd(t_finished *helper, int *exit_s, int *status);
void	exectution_helper(t_exec*exec, t_cmd *full, int perv_pipe);
void	close_helper(int inf, t_cmd *full, int *pipefd, int perv_pipe);
void	get_current_dir(t_env *env_list);
char	*add_dotdot_to_pwd(char *pwd, char *target);
void	update_pwd(char *oldpwd, char *newpwd, t_env *env);
void	printf_error(char *s);
int		*exit_status(int mode, int value);
void	print_error_arg(char *line_1, char *arg, char *line_2);
#endif
