
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
	if (isatty(STDIN_FILENO))
	{
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
				t_cmd *f =  parse_tokens(tokens);
				exectution(f, env_list, exit_s);
				free(line);
			}
			i++;
		}
		free(line);
		ft_malloc(0, 0);
		return (exit_s);
	}
}

