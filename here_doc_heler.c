/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_heler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:27:34 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/03 00:29:50 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_token(char **token_value, char *exp)
{
	if (!token_value || !exp)
		return ;
	*token_value = ft_strdup(exp);
	if (!*token_value)
		return ;
}

int	pick_limiter(char *next, char *limiter)
{
	int	result;

	if (!next[0] && !limiter[0])
		return (0);
	result = ft_strcmp(next, limiter);
	return (result);
}

char	*expnd_heredoc(char *input, t_env *env)
{
	int		help;
	int		i ;
	int		start;
	char	*repl;
	char	*result;

	start = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			if (i > start)
				result = ft_strjoin(result, ft_substr(input, start, i - start));
			repl = take_replace(i, input, &help, env);
			result = ft_strjoin(result, repl);
			i = help;
			start = i;
		}
		else
			i++;
	}
	if (i > start)
		result = ft_strjoin(result, ft_substr(input, start, i - start));
	return (result);
}
