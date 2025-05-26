/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:31:19 by abouabba          #+#    #+#             */
/*   Updated: 2025/05/24 11:23:40 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redirection(t_token *tokens)
{
	return (tokens->type == TOKEN_HEREDOC || tokens->type == TOKEN_APPEND ||
		tokens->type == TOKEN_REDIR_OUT || tokens->type == TOKEN_REDIR_IN);
}

int	syntax_2(t_token **tokens, int *exit_s)
{
	if (is_redirection(*tokens))
	{
		if (!(*tokens)->next || (*tokens)->next->type == TOKEN_EOF
			|| (*tokens)->next->type == TOKEN_PIPE
			|| is_redirection((*tokens)->next))
		{
			*exit_s = 2;
			fprintf(stderr, "minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
	}
	if ((*tokens)->type == TOKEN_PIPE)
	{
		if (!(*tokens)->next || (*tokens)->next->type == TOKEN_EOF)
		{
			*exit_s = 2;
			fprintf(stderr, "minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
	}
	return (0);
}

int	syntax(t_token *tokens, int *exit_s, int max_here_doc)
{
	if (!tokens || !tokens->value)
	{
		*exit_s = 2;
		return (1);
	}
	if (tokens->type == TOKEN_PIPE)
	{
		*exit_s = 2;
		fprintf(stderr, "minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	while (tokens)
	{
		if (tokens->type ==  TOKEN_HEREDOC)
		{
			max_here_doc++;
			if (max_here_doc > 16)
			{
				fprintf(stderr, "bash: maximum here-document count exceeded\n");
				*exit_s = 2;
				return (1);
			}
		}
		if(syntax_2(&tokens, exit_s))
			return (1);
		if (*exit_s == 2)
			return (0);
		tokens = tokens->next;
	}
	return (0);
}
