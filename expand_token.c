/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:31:34 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/27 02:37:19 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *take_token(char *string, t_env *env, int *exit_s)
{
	int i = 0;
	int quote = 0;
	int a = 0;
	int size;
	char *result;
	char *tmp;
	int t;
	
	if (!string)
		return (NULL);
	size = size_help(string, env, exit_s);
	result = ft_malloc(size + 2, 1);
	while (string[i])
	{
		if ((string[i] == '\'' || string[i] == '"') && quote == 0)
			quote = string[i];
		else if (string[i] == quote)
			quote = 0;
		if (string[i] == '$' && quote != '\'')
		{
			i++;
			if (string[i] && (ft_isalpha(string[i]) || ft_isdigit(string[i]) || string[i] == '_'))
			{
				
				tmp = ft_take(string, &i, env);
				t = 0;
				if (!tmp)
				{
					env->emg_flag = 1;
					tmp=ft_strdup("");
				}
				if (tmp[0] == '\0')
					env->emg_flag = 1;
				while (tmp[t])
						result[a++] = tmp[t++];
			}
			else if (string[i] == '?')
			{
				char *ext_s = ft_itoa(*exit_s);
				int you = 0;
				while (ext_s[you])
					result[a++] = ext_s[you++];
				i++;
			}
			else if (string[i] == '$')
			{
				if (string[i] == '$')
				{
					result[a++] = '$';
					i++;
				}
			}
			else
			{
				result[a++] = '$';
				if (string[i])
					result[a++] = string[i++];
			}
		}
		else
			result[a++] = string[i++];
	}
	result[a] = '\0';
	return result;
}
