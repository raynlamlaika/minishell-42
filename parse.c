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