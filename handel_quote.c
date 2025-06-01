/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:27:12 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/30 21:27:39 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
