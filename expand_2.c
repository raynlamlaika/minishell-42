/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:00:15 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/19 10:49:18 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tmp_null(char*tmp, t_env*env)
{
	if (!tmp)
	{
		env->emg_flag = 1;
		tmp = ft_strdup("");
	}
	else
		return (tmp);
	return (tmp);
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
	result = tmp_null (result, env);
	quote_helper_s_d(result);
	return (result);
}

int	expnd_size(char*string, int *i, t_env *env)
{
	int		help;
	int		size;
	char	*search;
	char	*result;

	(1) && (help = *i, size = 0);
	while (string[help] && help > 0)
	{
		if (string[help] == '$')
			(1) && (help--, size++);
		else
			break ;
	}
	if (size % 2 == 0)
	{
		help = *i;
		while (ft_isalpha(string[help]) || ft_isdigit(string[help]))
			help++;
		search = ft_substr(string, *i, help);
		result = ft_replace(search, env);
		(1) && (size = ft_strlen(result), *i = help);
	}
	else
		return (helper_mltp_dlar(i, string));
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
