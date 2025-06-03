/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:05:46 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/03 00:29:10 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*helpe_str_c(char *string, char *result, t_env *env, int *exit_s)
{
	t_expand_state	st;

	st.i = 0;
	st.a = 0;
	st.env = env;
	st.exit_s = exit_s;
	while (string[st.i])
	{
		if (string[st.i] == '$')
		{
			st.i++;
			handle_dollar_case(string, result, &st);
		}
		else
			result[st.a++] = string[st.i++];
	}
	result[st.a] = '\0';
	return (result);
}

int	size_help_doc(char *string, t_env *env, int *exit_s)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (string[i])
	{
		if (string[i] == '$')
		{
			i++;
			if (string[i] == '$')
				(1) && (size++, i++);
			else if (ft_isalpha(string[i]) || \
ft_isdigit(string[i]) || string[i] == '_')
				size += expnd_size(string, &i, env);
			else
			{
				size_helper(exit_s, string, i, &size);
				i++;
			}
		}
		else
			(1) && (size++, i++);
	}
	return (size);
}

char	*take_token_doc(char *string, t_env *env, int *exit_s)
{
	int		size;
	char	*result;

	if (!string)
		return (NULL);
	size = size_help_doc(string, env, exit_s);
	printf("thi sis the sie %d\n", size);
	result = ft_malloc(size + 2, 1);
	return (helpe_str_c(string, result, env, exit_s));
}
