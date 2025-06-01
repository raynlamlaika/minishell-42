/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:31:34 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/01 11:57:55 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_expans
{
	char	*result;
	char	*tmp;
	int		i;
	int		quote;
	int		a;
	int		size;
	int		t;
}			t_expans;

void	expand_exits_s(int *exit_s, char *result, int *a, int *i)
{
	char	*ext_s;
	int		you;

	ext_s = ft_itoa(*exit_s);
	you = 0;
	while (ext_s[you])
		result[(*a)++] = ext_s[you++];
	(*i)++;
}

char	*expaned_ed(char*string, t_env *env, int i)
{
	char	*tmp;

	tmp = ft_take(string, &i, env);
	if (!tmp)
	{
		env->emg_flag = 1;
		tmp = ft_strdup("");
	}
	if (tmp[0] == '\0')
		env->emg_flag = 1;
	return (tmp);
}

void	handle_quote_state(char c, int *quote)
{
	if ((c == '\'' || c == '"') && *quote == 0)
		*quote = c;
	else if (c == *quote)
		*quote = 0;
}

int	handle_dollar_case(char *str, char *result, t_expand_state *st)
{
	char	*tmp;
	int		t;

	if (str[st->i] && (ft_isalpha(str[st->i]) || ft_isdigit(str[st->i]) || str[st->i] == '_'))
	{
		(1) && (tmp = ft_take(str, &st->i, st->env), t = 0);
		if (tmp[0] == '\0')
			st->env->emg_flag = 1;
		while (tmp[t])
			result[st->a++] = tmp[t++];
	}
	else if (str[st->i] == '?')
		expand_exits_s(st->exit_s, result, &st->a, &st->i);
	else if (str[st->i] == '$')
	{
		if (str[st->i++] == '$')
			result[st->a++] = '$';
	}
	else
	{
		result[st->a++] = '$';
		if (str[st->i])
			result[st->a++] = str[st->i++];
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
		else
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
