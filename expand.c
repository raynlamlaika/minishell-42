/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 04:32:41 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/27 08:28:22 by rlamlaik         ###   ########.fr       */
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

char	*add_quotes(char *str)
{
	char	*equal_sign;
	char	*result;
	int		key_len;
	int		value_len;

	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
		return (ft_strdup(str));
	key_len = equal_sign - str;
	value_len = strlen(equal_sign + 1);
	result = ft_malloc(key_len + 1 + 1 + value_len + 1 + 1, 1);
	if (!result)
		return (NULL);
	strncpy(result, str, key_len);
	result[key_len] = '=';
	result[key_len + 1] = '"';
	strcpy(result + key_len + 2, equal_sign + 1);
	result[key_len + 2 + value_len] = '"';
	result[key_len + 2 + value_len + 1] = '\0';
	return (result);
}

void	process_token_dollar(t_token *token, t_env *env, int *exit_s, int one)
{
	char	*res;

	if (one == 1337)
		token->value = add_quotes(token->value);
	res = take_token(token->value, env, exit_s);
	if (res[0] == '\0')
		token->ambiguous = " ";
	if (env->emg_flag)
	{
		token->ambiguous = token->value;
		token->hlep = 1312;
	}
	replace_token(&token->value, s_split(res, token, hendel_qoutes(token->value)));
}

void	process_token_quotes(t_token *token)
{
	if (ft_strchr(token->value, '\'') || ft_strchr(token->value, '\"'))
		replace_token(&token->value, hendel_qoutes(token->value));
}

void	expand(t_token *token, t_env *env, int *exit_s)
{
	int	export_h;
	int	one;

	(1) && (export_h = 0, one = 0);
	while (token && token->value)
	{
		if (ft_strcmp("export", token->value) == 0 && export_h == 0)
			one = 1337;
		else if (ft_strcmp("export", \
			hendel_qoutes(token->value)) == 0 && export_h == 0)
			one = 42;
		if (token->type == TOKEN_HEREDOC)
		{
			token = token->next;
			if (token)
				token = token->next;
		}
		if (ft_strchr(token->value, '$'))
			process_token_dollar(token, env, exit_s, one);
		else
			process_token_quotes(token);
		if (is_redirection(token) || token->type == TOKEN_PIPE)
			one = 0;
		(1) && (token = token->next, export_h++);
	}
}

/*
void take_dolar_sgin()
{
	if (one == 1337)
	token->value = add_quotes(token->value);
	res = take_token(token->value, env, exit_s);
	if (res[0] == '\0')
		token->ambiguous = " ";
	if (env->emg_flag)
	{
		token->ambiguous = token->value;
		token->hlep = 1312;
	}
	s_split(res, token, hendel_qoutes(token->value));
}
void	expand(t_token *token, t_env *env, int *exit_s)
{
	int		export_h;
	int		one;
	char	*res;

	(1) && (export_h = 0, one = 0);
	while (token && token->value)
	{
		if (ft_strcmp("export", token->value) == 0 && export_h == 0)
			one = 1337;
		else if (ft_strcmp("export", \\
		hendel_qoutes(token->value)) == 0 && export_h == 0)
			one = 42;
		if (token->type == TOKEN_HEREDOC)
		{
			token = token->next;
			if (token)
				token = token->next;
		}
		if (ft_strchr(token->value, '$'))
		{
			if (one == 1337)
				token->value = add_quotes(token->value);
			res = take_token(token->value, env, exit_s);
			if (res[0] == '\0')
				token->ambiguous = " ";
			if (env->emg_flag)
			{
				token->ambiguous = token->value;
				token->hlep = 1312;
			}
			s_split(res, token, hendel_qoutes(token->value));
		}
		else if (ft_strchr(token->value, '\'') || ft_strchr(token->value, '\"'))
			replace_token(&token->value, hendel_qoutes(token->value));
		if (is_redirection(token) || token->type == TOKEN_PIPE)
			one = 0;
		(1) && (token = token->next, export_h++);
	}
}
*/