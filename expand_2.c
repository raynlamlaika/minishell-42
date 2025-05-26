/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:00:15 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/26 01:58:20 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_token(char **token_value, char *exp)
{
	if (!token_value || !exp)
		return ;
	*token_value = ft_strdup(exp);
	if (!*token_value)
	{
		perror("replace_token: strdup failed");
		exit(EXIT_FAILURE);
	}
}

char	*ft_take(char *string, int *i, t_env *env)
{
	int		help;
	char	*search;
	char	*result;

	help = *i;
	while (ft_isalpha(string[help]) || ft_isdigit(string[help]))
		help++;
	search = ft_substr(string, *i, help);
	result = ft_replace(search, env);
	*i = help;
	return (result);
}

int	expnd_size(char*string, int *i, t_env *env)
{
	int		help;
	int		size;
	char	*search;
	char	*result;

	help = *i;
	while (ft_isalpha(string[help]) || ft_isdigit(string[help]))
		help++;
	search = ft_substr(string, *i, help);
	result = ft_replace(search, env);
	size = ft_strlen(result);
	*i = help;
	return (size);
}

void	size_helper(int *exit_s, char *string, int i, int *size)
{
	if (string[i] == '$')
		*size += 1;
	else if (string[i] == '?')
		*size += ft_strlen(ft_itoa(*exit_s));
	else
		(*size)++;
}

int	size_help(char *string, t_env *env, int *exit_s)
{
	int	size;
	int	quote;
	int	i;

	1 && (size = 0, quote = 0, i = 0);
	while (string[i])
	{
		if ((string[i] == '\'' || string[i] == '"') && quote == 0)
			quote = string[i];
		else if (string[i] == quote)
			quote = 0;
		if (string[i] == '$' && quote != '\'')
		{
			if (string[++i] == '$')
				size++;
			else if (ft_isalpha(string[i]) || ft_isdigit(string[i]) \
				|| string[i] == '_')
				size += expnd_size(string, &i, env);
			else
				size_helper(exit_s, string, i, &size);
		}
		else
			1 && (size++, i++);
	}
	return (size);
}
