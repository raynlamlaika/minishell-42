/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_h.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 03:19:30 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/19 11:53:55 by abouabba         ###   ########.fr       */
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

void	process_token_quotes(t_token *token)
{
	if (ft_strchr(token->value, '\'') || ft_strchr(token->value, '\"'))
		replace_token(&token->value, hendel_qoutes(token->value));
}

void	check(t_token *token, t_env *env, int export_h, int *one)
{
	if (ft_strcmp(token->value, "~") == 0)
		replace_token(&token->value, expnd_cd("HOME", env));
	if (ft_strcmp("export", token->value) \
	== 0 && export_h == 0 && ft_strchr(token->value, '=') == NULL)
		*one = 1337;
}
