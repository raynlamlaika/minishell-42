/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_imbg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 04:52:53 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/24 11:23:40 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rederaction_help(t_token *tokens)
{
	return (tokens->type == TOKEN_APPEND || tokens->type == TOKEN_REDIR_IN
		|| tokens->type == TOKEN_REDIR_OUT);
}
void helper_function(t_token *tokens)
{
	if(tokens)
		if (tokens->hlep == 1312)
			tokens->value = ft_strdup("");	
}

int	syntax_ambiguous(t_token *tokens, int *exit_s)
{
	while (tokens)
	{
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
		helper_function(tokens);
		if (!tokens)
			return (0);
	}
	return (0);
}
