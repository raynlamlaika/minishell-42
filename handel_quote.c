/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:27:12 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/19 10:45:39 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void restore_hidden_q(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i])
	{
		if ((unsigned char)str[i] == 30)
			str[i] = 39;
		else if ((unsigned char)str[i] == 31)
			str[i] = 34;
		i++;
	}
}

char	*hendel_qoutes(char *str)
{
	int		i;
	int		a;
	char	quote;
	char	*result;

	(1) && (i = 0, a = 0, quote = 0, result = ft_malloc(ft_strlen(str) + 1, 1));
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (quote == 0)
				quote = str[i++];
			else if (str[i] == quote)
			{
				quote = 0;
				i++;
			}
			else
				result[a++] = str[i++];
		}
		else
			result[a++] = str[i++];
	}
	result[a] = '\0';
	return (result);
}
