
#include"minishell.h"

int main(int ac,char **av,char**env)
{
	static int exit_s;
	char *line;
	t_token *tokens;
	t_token* last = NULL;
	t_env	*env_list;

	(void)av;
	ac =1;
	int i = 1;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while(i)
	{
		exit_s = 0;
		line = readline("minishell $> ");
		if (!line) 
		{
			perror("readline");
			free(line);
			ft_malloc(0, 0);
			return 1;
		}
		add_history(line);
		tokens = lexer(line, last, 0);
		env_list = linked_varibles(env);
		expand(tokens, env_list);
		syntax(tokens, &exit_s);
		if (exit_s == 0)
		{
			printf("this is %d\n", exit_s);
			t_cmd *f =  parse_tokens(tokens);
			// heredoc(f->file, env_list);
			exectution(f, env_list);
			i++;
			free(line);
		}
		else
		{
			printf("this is %d\n", exit_s);
			free(line);
			ft_malloc(0, 0);
		}
	}
	free(line);
	ft_malloc(0, 0);
	return (exit_s);
}

