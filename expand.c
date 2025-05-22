/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 04:32:41 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/22 12:10:59 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*

realSHELL $> cat << s
here_doc >> $askfjaldsjfas
here_doc >> jafj
here_doc >> s


cat
^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

\

ELL $> ls $a
ls: cannot access '$a': No such file or directory
realSHELL $> echo $a
a

*/



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
// char* add_quotes(char *str)
// {
// 	char *result;
	
// 	if (ft_strchr(str, "="))
// 	{
// 		take_value(str);
// 	}

// 	result = ft_malloc(ft_strlen(str) + 3, 1);// first quoy=te and sec and the null treminetor
// 	result[0] = '"';
// 	int y = 1;
// 	int p = 0;
// 	while (str[p])
// 	{
// 		result[y] = str[p];
// 		y++;
// 		p++;
// 	}
// 	result[y] ='"';
// 	result[++y] ='\0';
// 	return (result);
// }

char *add_quotes(char *str)
{
    char *equal_sign = ft_strchr(str, '=');
    if (!equal_sign)
        return ft_strdup(str); // No '=', return copy of original string

    int key_len = equal_sign - str;
    int value_len = strlen(equal_sign + 1);

    char *result = ft_malloc(key_len + 1 + 1 + value_len + 1 + 1, 1);
    if (!result)
        return NULL;

    // Copy key
    strncpy(result, str, key_len);
    result[key_len] = '=';

    // Add opening quote
    result[key_len + 1] = '"';

    // Copy value
    strcpy(result + key_len + 2, equal_sign + 1);

    // Add closing quote and null terminator
    result[key_len + 2 + value_len] = '"';
    result[key_len + 2 + value_len + 1] = '\0';

    return result;
}


void	expand(t_token *token, t_env *env, int *exit_s)
{
	int export_h = 0;
	int one= 0;
	char	*res;
	t_token *prev;

	prev = NULL;
	while (token && token->value)
	{
		if (ft_strcmp("export", token->value) == 0 && export_h == 0)
			one = 1337;
		else if (ft_strcmp("export", hendel_qoutes(token->value)) == 0 && export_h == 0)
			one = 42;
		if (token->type == TOKEN_HEREDOC)
		{
			token = token->next;
			token = token->next;
		}
		if (ft_strchr(token->value, '$'))
		{
			if (one == 1337)
				token->value = add_quotes(token->value);
			res = take_token(token->value, env, exit_s);
			if (res[0] == '\0')
				printf("need to remove the node %s and %s\n", token->value, res);
			if (env->emg_flag)
				token->flag_mbg = 1;
			s_split(res, token, hendel_qoutes(token->value));
		}
		else if (ft_strchr(token->value, '\'') || ft_strchr(token->value, '\"'))
			replace_token(&token->value, take_token(token->value, env , exit_s));
		if (is_redirection(token) || token->type == TOKEN_PIPE)
			one = 0;
		prev = token;
		token = token->next;
		export_h++;
	}
}
