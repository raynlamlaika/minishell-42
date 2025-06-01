/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:31:19 by abouabba          #+#    #+#             */
/*   Updated: 2025/06/01 23:10:10 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(t_token *tokens)
{
	return (tokens->type == TOKEN_HEREDOC || tokens->type == TOKEN_APPEND || \
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
			fprintf(stderr, "minishell: \
syntax error near unexpected token `newline'\n");
			return (1);
		}
	}
	if ((*tokens)->type == TOKEN_PIPE)
	{
		if (!(*tokens)->next || (*tokens)->next->type == TOKEN_EOF)
		{
			*exit_s = 2;
			fprintf(stderr, "minishell: \
syntax error near unexpected token `newline'\n");
			return (1);
		}
	}
	return (0);
}

char	*add_quotessss(char *input)
{
	int		len;
	char	*quoted;

	len = strlen(input);
	quoted = ft_malloc(len + 3, 1);
	if (!quoted)
		return (NULL);
	quoted[0] = '\"';
	strcpy(quoted + 1, input);
	quoted[len + 1] = '\"';
	quoted[len + 2] = '\0';
	return (quoted);
}

int	syntax(t_token *tokens, int *exit_s, int max_here_doc)
{
	if (!tokens || !tokens->value)
	{
		*exit_s = 2;
		return (1);
	}
	if (tokens->type == TOKEN_PIPE)
		return (*exit_s = 2, \
fprintf(stderr, "minishell: syntax error near unexpected token `|'\n"), 1);
	while (tokens)
	{
		if (tokens->type == TOKEN_HEREDOC)
		{
			max_here_doc++;
			if (max_here_doc > 16)
			{
				fprintf(stderr, "bash: maximum here-document count exceeded\n");
				*exit_s = 2;
				return (1);
			}
		}
		if (syntax_2(&tokens, exit_s))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
