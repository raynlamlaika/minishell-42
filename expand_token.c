/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:31:34 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/12 10:25:06 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote_state(char c, int *quote)
{
	if ((c == '\'' || c == '"') && *quote == 0)
		*quote = c;
	else if (c == *quote)
		*quote = 0;
}

int	check_valid(char h)
{
	if (h && (ft_isalpha(h) || ft_isdigit(h) || h == '_'))
		return (1);
	return (0);
}

int	handle_dollar_case(char *l, char *result, t_expand_state *st)
{
	char	*tmp;
	int		t;

	if (check_valid(l[st->i]))
	{
		(1) && (tmp = ft_take(l, &st->i, st->env), t = 0);
		if (tmp[0] == '\0')
			st->env->emg_flag = 1;
		while (tmp[t])
			result[st->a++] = tmp[t++];
	}
	else if (l[st->i] == '?')
		expand_exits_s(st->exit_s, result, &st->a, &st->i);
	else if (l[st->i] == '$')
	{
		if (l[st->i++] == '$')
			result[st->a++] = '$';
	}
	else
	{
		result[st->a++] = '$';
		if (l[st->i])
			result[st->a++] = l[st->i++];
	}
	return (0);
}

char	*helpe_str(char *string, char *result, t_env *env, int *exit_s)
{
	int				quote;
	t_expand_state	st;

	quote = 0;
	st.i = 0;
	st.a = 0;
	st.env = env;
	st.exit_s = exit_s;
	while (string[st.i])
	{
		handle_quote_state(string[st.i], &quote);
		if (string[st.i] == '$' && quote != '\'')
		{
			st.i++;
			handle_dollar_case(string, result, &st);
		}
		else if (string[st.i])
			result[st.a++] = string[st.i++];
	}
	result[st.a] = '\0';
	return (result);
}

char	*take_token(char *string, t_env *env, int *exit_s)
{
	int		size;
	char	*result;

	if (!string)
		return (NULL);
	size = size_help(string, env, exit_s);
	result = ft_malloc(size + 2, 1);
	return (helpe_str(string, result, env, exit_s));
}
