/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_imbg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 04:52:53 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/31 21:36:09 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rederaction_help(t_token *tokens)
{
	return (tokens->type == TOKEN_APPEND || tokens->type == TOKEN_REDIR_IN
		|| tokens->type == TOKEN_REDIR_OUT);
}

int	synx_ambg(t_token *tokens, int *exit_s)
{
	while (tokens)
	{
		tokens->rm_node = 0;
		if (tokens->ambiguous && \
tokens->type != TOKEN_EOF && tokens->value[0] == '\0')
			tokens->rm_node = 10;
		if (rederaction_help(tokens))
		{
			tokens = tokens->next;
			if (tokens->hlep == 1312)
				return (fprintf(stderr, "%s: ambiguous\
redirect\n", tokens->ambiguous), *exit_s = 1, 1);
			if (tokens->ambiguous)
			{
				tokens = tokens->next;
				if (tokens->ambiguous)
					return (fprintf(stderr, "%s: ambiguous\
redirect\n", tokens->ambiguous), *exit_s = 1, 1);
			}
		}
		tokens = tokens->next;
		if (!tokens)
			return (0);
	}
	return (0);
}
