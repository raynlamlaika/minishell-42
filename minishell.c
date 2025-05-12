
#include"minishell.h"

int main(int ac,char **av,char**env)
{
	static int exit_s;
	static int here_doc;
	char *line;
	t_token *tokens;
	t_token* last = NULL;
	// t_env	**head_env;
	t_env	*env_list;

	(void)av;

	ac =1;
	int g = 0;
	int i = 1;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	env_list = linked_varibles(env); // ne to free        void	free_env_list(t_env *head)
	if (isatty(STDIN_FILENO))
	{
		while(i)
		{
			g = 0;
			line = readline("minishell $> ");
			if (!line) 
			{
				ft_malloc(0, 0);
				return (1);
			}
			add_history(line);
			tokens = lexer(line, last, 0);
			if (tokens)
				g = syntax(tokens, &exit_s, here_doc);
			if (g == 0)
			{
				expand(tokens, env_list);
				t_cmd *f =  parse_tokens(tokens,env_list);
				exectution(f, env_list, exit_s);
				free(line);
			}
			ft_malloc(0, 0);
			i++;
			// print_env_list(env_list);
		}
		free(line);
		ft_malloc(0, 0);
		free_env_list(env_list);
		return (exit_s);
	}
}

