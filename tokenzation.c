/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenzation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:17:40 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/04/09 17:15:31 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_word(t_token **head, t_token **last, char *input, int *i)
{
    int start = *i;
    int j = *i;
    int in_quotes = 0;
    char quote_char = 0;

	
    while (input[j] && (in_quotes || (!strchr(" |\n", input[j]))))
    {
        if ((input[j] == '"' || input[j] == '\''))
        {
            if (!in_quotes)
            {
                in_quotes = 1;
                quote_char = input[j];
            }
            else if (input[j] == quote_char)
            {
                in_quotes = 0;
            }
        }
        j++;
    }
    char *word = strndup(input + start, j - start);
    append_token(head, last, TOKEN_WORD, word);
    *i = j - 1;
}

void	append_token(t_token **head, t_token **last, t_token_type type, char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		exit(1); //need to fix
	new->type = type;
	if (value)
		new->value = strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
		(*last)->next = new;
	*last = new;
}

t_token *lexer(char *input, int i,t_token* last)
{
	t_token *head = NULL;

    while (input[i] && input[i] != '\n')
    {
        if (input[i] == ' ')
            ;
        else if (input[i] == '|')
            append_token(&head, &last, TOKEN_PIPE, "|");
        else if (input[i] == '<' && input[i + 1] == '<')
            append_token(&head, &last, TOKEN_HEREDOC, "<<"), i++;
        else if (input[i] == '>' && input[i + 1] == '>')
            append_token(&head, &last, TOKEN_APPEND, ">>"), i++;
        else if (input[i] == '<')
            append_token(&head, &last, TOKEN_REDIR_IN, "<");
        else if (input[i] == '>')
            append_token(&head, &last, TOKEN_REDIR_OUT, ">");
        else if (input[i] == '"')
            handle_quotes(&head, &last, input, &i, '"');
        else if (input[i] == '\'')
            handle_quotes(&head, &last, input, &i, '\'');
        else
            handle_word(&head, &last, input, &i);
        i++;
    }
    return (append_token(&head, &last, TOKEN_EOF, NULL), head);
}
