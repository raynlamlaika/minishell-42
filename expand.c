/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 04:32:41 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/15 14:06:59 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_token(char *string, t_env *env)
{
	int i = 0;
	int quote = 0;
	int a = 0;
	int size;
	char* result;
	char *tmp;
	int t;

	size = size_help(string, env);
	result = ft_malloc(size + 1, 1);
	while (string[i])
	{
		if ((string[i] == '\'' || string[i] == '"') && quote == 0)
			quote = string[i];
		else if (string[i] == quote)
			quote = 0;
		if (string[i] == '$' && quote != '\'')
		{
			i++;
			if(ft_isalpha(string[i]) || ft_isdigit(string[i]) || string[i] == '_')
			{
				t = 0;
				tmp = ft_take(string, &i, env);
				while(tmp[t])
					result[a++] = tmp[t++];
			}
			else
				if (string[i] == '$' || string[i] == '?')
					result[a++] = '$';
		}
		else
			result[a++] = string[i++];
	}
	return(result[a] = '\0', result);
}

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

char *hendel_qoutes(char *string)
{
    int i = 0;
    int a = 0;
    char quote = 0;
    char *result = ft_malloc(ft_strlen(string) + 1, 1);

    while (string[i])
    {
        if (string[i] == '\'' || string[i] == '"')
        {
            if (quote == 0)
                quote = string[i++];
            else if (string[i] == quote)
            {
                quote = 0;
                i++;
            }
            else
                result[a++] = string[i++];
        }
        else
            result[a++] = string[i++];
    }
    result[a] = '\0';

    return result;
}


void	expand(t_token *token, t_env *env)
{
	while (token && token->value)
	{
		if (ft_strchr(token->value, '$'))
			s_split(take_token(token->value, env), token);
		else if (ft_strchr(token->value, '\'') || ft_strchr(token->value, '\"'))
		{
			replace_token(&token->value, hendel_qoutes(token->value));
		}
		token = token->next;
	}
}
