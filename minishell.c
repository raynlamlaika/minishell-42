
#include"minishell.h"

int main(int ac,char **av,char**env)
{
	static int exit_s = 128;
	char *line;
	t_token *tokens;
	t_token* last = NULL;
	t_env	*env_list;

	(void)av;

	ac =1;
	int i = 1;
	while(i)
	{
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
		syntax(tokens, exit_s);
		t_cmd *f =  parse_tokens(tokens);
		heredoc(f->file, env_list);
		exectution(f, env_list);
		free(line);
		i++;
	}
	free(line);
	ft_malloc(0, 0);
	return (exit_s);
}

