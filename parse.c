#include "minishell.h"

int is_redirection(t_token *tokens)
{
	return (tokens->type == TOKEN_HEREDOC || tokens->type == TOKEN_APPEND ||
		tokens->type == TOKEN_REDIR_OUT || tokens->type == TOKEN_REDIR_IN ||
		tokens->type == TOKEN_PIPE);
}

void syntax(t_token *tokens)
{
	if (!tokens || tokens->type == TOKEN_PIPE)
	{
		printf ("error syntax\n");
		exit(1);
	}
	while(tokens)
	{
		if (is_redirection(tokens))
		{
			if (!tokens->next)
			{
				printf("syntax error\n");
				exit(1);
			}
			if (tokens->next->type == TOKEN_PIPE)
			{
				printf ("syntax error\n");
				exit (1);
			}
			if (is_redirection(tokens->next))
			{
				printf ("syntax error\n");
				exit(1);
			}
		}
		if (tokens->type == TOKEN_PIPE)
		{
			if (tokens->next->type == TOKEN_EOF)
			{
				printf("syntax errr\n");
				exit(1);
			}
		}
		tokens = tokens->next;
	}
}

void add_arg(t_cmd *type, char *value)
{
	int	count;
	char **new_args;

	count = 0;
	if (type->args)
	{
		while (type->args[count])
			count++;
	}
	new_args = malloc(sizeof(char *) * (count + 2));
	// while (value)
	// // ...
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd *type;

	type = malloc(sizeof(t_cmd));

	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD)
			add_arg(type, tokens->value);
		else if (tokens->type == TOKEN_REDIR_IN && tokens->next)
			type->infile = tokens->next->value;
		else if (tokens->type == TOKEN_REDIR_OUT && tokens->next)
		{
			type->outfile = tokens->next->value;
			type->append = 0;
		}
		else if (tokens->type == TOKEN_APPEND && tokens->next)
		{
			type->outfile = tokens->next->value;
			type->append = 1;
		}
		tokens = tokens->next;
	}
	printf("infile: %s\n", type->infile);
	printf("outfile: %s\n", type->outfile);
	printf("append: %d\n", type->append);
	if (type->args)
		for (int j = 0; type->args[j]; j++)
			printf("arg[%d]: %s\n", j, type->args[j]);

	return(type);

}
