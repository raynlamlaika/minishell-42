/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:46:42 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/04/10 22:06:24 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_token(t_token **head, \
t_token **last, t_token_type type, char *value)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token), 1);
	new->ambiguous = NULL;
	new->type = type;
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	new->ambiguous = 0;
	new->flag_mbg = 0;
	if (!*head)
		*head = new;
	else
		(*last)->next = new;
	*last = new;
}

void	handle_quotes(t_token **head, t_token **last, char *input, int *i)
{
	int		start;
	int		len;
	char	*word;
	char	quote;

	quote = input[*i];
	start = *i;
	len = 0;
	(*i)++;
	while (input[*i] && input[*i] != quote)
	{
		(*i)++;
		len++;
	}
	if (input[*i] == quote)
		(*i)++;
	while (input[*i] && (' ' != input[*i]) && !ft_strchr("><|\n", input[*i]))
	{
		(*i)++;
		len++;
	}
	word = ft_strndup(input + start, *i - start);
	append_token(head, last, TOKEN_WORD, word);
	(*i)--;
}

void	handle_word(t_token **head, t_token **last, char *input, int *i)
{
	int		start;
	int		j;
	int		in_quotes;
	char	quote_char;
	char	*word;

	start = *i;
	(1) && (in_quotes = 0, quote_char = 0, j = *i);
	while (input[j] && (in_quotes || (!ft_strchr(" |<>\n", input[j]))))
	{
		if ((input[j] == '"' || input[j] == '\''))
		{
			if (!in_quotes)
			{
				in_quotes = 1;
				quote_char = input[j];
			}
			else if (input[j] == quote_char)
				in_quotes = 0;
		}
		j++;
	}
	word = ft_strndup(input + start, j - start);
	append_token(head, last, TOKEN_WORD, word);
	*i = j - 1;
}

t_token	*lexer(char *input, t_token*last, int i)
{
	t_token	*head;

	head = NULL;
	while (input[i] && input[i] != '\n')
	{
		if (input[i] == ' ' || input[i] == '\t')
			;
		else if (input[i] == '|')
			append_token(&head, &last, TOKEN_PIPE, "|");
		else if (input[i] == '<' && input[i + 1] == '<')
			(1) && (append_token(&head, &last, TOKEN_HEREDOC, "<<"), i++);
		else if (input[i] == '>' && input[i + 1] == '>')
			(1) && (append_token(&head, &last, TOKEN_APPEND, ">>"), i++);
		else if (input[i] == '<')
			append_token(&head, &last, TOKEN_REDIR_IN, "<");
		else if (input[i] == '>')
			append_token(&head, &last, TOKEN_REDIR_OUT, ">");
		else if (input[i] == '"' || input[i] == '\'')
			handle_quotes(&head, &last, input, &i);
		else
			handle_word(&head, &last, input, &i);
		i++;
	}
	return (append_token(&head, &last, TOKEN_EOF, NULL), head);
}
