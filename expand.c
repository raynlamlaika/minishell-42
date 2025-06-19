/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 04:32:41 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/19 18:59:44 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_quotes(char *str)
{
	char	*equal_sign;
	char	*result;
	int		key_len;
	int		value_len;

	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
		return (ft_strdup(add_quotessss(str)));
	key_len = equal_sign - str;
	value_len = ft_strlen(equal_sign + 1);
	result = ft_malloc(key_len + 1 + 1 + value_len + 1 + 1, 1);
	if (!result)
		return (NULL);
	ft_strncpy(result, str, key_len);
	result[key_len] = '=';
	result[key_len + 1] = '"';
	ft_strcpy(result + key_len + 2, equal_sign + 1);
	result[key_len + 2 + value_len] = '"';
	result[key_len + 2 + value_len + 1] = '\0';
	return (result);
}

int	is_inside_quotes(const char *str, int pos)
{
	int		i;
	char	quote;

	if (!str || pos < 0)
		return (0);
	i = 0;
	quote = 0;
	while (str[i] && i <= pos)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (quote == 0)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
		}
		i++;
	}
	if (quote != 0)
		return (1);
	return (0);
}

void	quote_helper_s_d(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] == 39)
			str[i] = 30;
		else if (str[i] == 34)
			str[i] = 31;
		i++;
	}
}

void	process_token_dollar(t_token *token, t_env *env, int *exit_s, int one)
{
	char	*res;

	token->hlep = 0;
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
	if (ft_strchr(res, ' ') && one != 1337)
		s_split(res, token, hendel_qoutes(token->value));
	else
		replace_token(&token->value, \
s_split(res, token, hendel_qoutes(token->value)));
}

int	expand(t_token *token, t_env *env, int *exit_s)
{
	int	export_h;
	int	one;

	(1) && (export_h = 0, one = 0);
	while (token && token->value)
	{
		if (ft_strcmp(token->value, "~") == 0)
			replace_token(&token->value, expnd_cd("HOME", env));
		if (helper_valid(token->value, export_h))
			one = 1337;
		if (token->type == TOKEN_HEREDOC)
		{
			token = token->next->next;
			if (token)
				continue ;
		}
		if (ft_strchr(token->value, '$'))
			process_token_dollar(token, env, exit_s, one);
		else
			process_token_quotes(token);
		if (is_redirection(token) || token->type == TOKEN_PIPE)
			one = 0;
		(1) && (token = token->next, export_h++);
	}
	return (1);
}
