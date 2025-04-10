/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:08:16 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/04/09 14:24:48 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes(t_token **head, t_token **last, \
						char *input, int *i, char quote)
{
	int		start;
	char	*word;

	start = *i;
	while (input[*i])
	{
		(*i)++;
		if (input[*i] && ft_strchr("|><\n", input[*i]) && input[*i] )
			break ;
	}
	word = strndup((input + start), (*i - start));
	append_token(head, last, TOKEN_WORD, word);
	(*i)--;
}

int	main(int ac, char **av, char**env)
{
	char	*line;
	t_token	*tokens;
	t_token	*last;
	int		i;

	i = 1;
	while (i)
	{
		line = readline("minishell$");
		if (!line)
		{
			perror("readline");
			free(line);
			return (1);
		}
		printf("it pas to tehe sy\n");
		tokens = lexer(line, 0, last);
		syntax(tokens);
		while (tokens)
		{
			printf("this is the value %s\n", tokens->value);
			tokens= tokens->next;
		}
		// parse_tokens(tokens);
		if (i >= 4)
			break ;
		i++;
	}
	free(line);
	return (0);
}
