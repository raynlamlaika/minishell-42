/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_ambiguous.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:16:50 by abouabba          #+#    #+#             */
/*   Updated: 2025/05/16 18:52:19 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int rederaction_help(t_token *tokens)
{
    return (tokens->type == TOKEN_APPEND || tokens->type == TOKEN_REDIR_IN
        || tokens->type == TOKEN_REDIR_OUT);
}

int syntax_ambiguous(t_token *tokens, int *exit_s)
{
    while (tokens)
    {
        if (rederaction_help(tokens))
        {
            tokens = tokens->next;
            if (tokens->ambiguous)
            {
                tokens = tokens->next;
                if (tokens->ambiguous)
                {
                    printf("%s: ambiguous redirect\n", tokens->ambiguous);
                    *exit_s = 1;
                    return (1);
                }
            }
        }
        tokens = tokens->next;
    }
    return (0);
}
