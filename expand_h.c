/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_h.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 03:19:30 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/02 03:21:04 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_replace(int i, char *input, int *help, t_env *env)
{
	int		start;
	int		len;
	char	*val;
	char	*key;

	len = 0;
	start = i + 1;
	if (!ft_isalpha(input[start]) && input[start] != '_')
		return (*help = start, ft_strdup("$"));
	while (ft_isalnum(input[start + len]) || input[start + len] == '_')
		len++;
	*help = start + len;
	key = ft_substr(input, start, len);
	val = ft_strdup("");
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			val = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	return (val);
}
