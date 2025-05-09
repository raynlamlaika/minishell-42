
#include"minishell.h"

int main(int ac,char **av,char**env)
{
	static int exit_s;
	static int here_doc;
	char *line;
	t_token *tokens;
	t_token* last = NULL;
	t_env	*env_list;

	(void)av;

	ac =1;
	int i = 1;
	env_list = linked_varibles(env);
	if (1)
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
				return (1);
			}
			add_history(line);
			tokens = lexer(line, last, 0);
			if (tokens)
			{
				syntax(tokens, &exit_s, here_doc);
			}
			expand(tokens, env_list);
			t_cmd *f =  parse_tokens(tokens,env_list);
			if (exit_s == 0)
			{
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

