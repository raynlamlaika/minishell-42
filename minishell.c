
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
			perror("readFFFFline");
			free(line);
			return 1;
		}
		add_history(line);
		tokens = lexer(line, last, 0);
	
		// while (tokens)
		// {
		// 	printf("thsis %s\n", tokens->value);
		// 	tokens = tokens->next;
		// }
		env_list = linked_varibles(env);
		// check_expeand();
		// get_value(env_list, "PATHH"); it's just in check for the func check value 
		syntax(tokens, exit_s);
		//faild in the syntax 
		t_cmd *f = parse_tokens(tokens);
		// here will be the expanding 
		exectution(f, env_list);
		// the expande
		// if(i >= 4)
		// 	break;
		i++;
	}
	free(line);
	return (exit_s);
}
