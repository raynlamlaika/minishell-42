/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:37:39 by abouabba          #+#    #+#             */
/*   Updated: 2025/06/01 15:32:06 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	char			*s;
	size_t			p;

	i = 0;
	p = size * count;
	if (size && p / size != count)
		return (0);
	s = (char *)ft_malloc(size * count, 1);
	if (!s)
		return (NULL);
	while (i < (size * count))
	{
		s[i] = 0;
		i++;
	}
	return (s);
}

t_token	*parse_tokens_helper(t_token *tokens,
	t_file **last_file, t_file *file, t_env *env)
{
	if (tokens->type == TOKEN_REDIR_IN && tokens->next)
	{
		token_infile(last_file, file, tokens);
		tokens = tokens->next;
	}
	else if (tokens->type == TOKEN_REDIR_OUT && tokens->next)
	{
		token_outfile(last_file, file, tokens);
		tokens = tokens->next;
	}
	else if (tokens->type == TOKEN_APPEND && tokens->next)
	{
		token_append(last_file, file, tokens);
		tokens = tokens->next;
	}
	else if (tokens->type == TOKEN_HEREDOC && tokens->next)
	{
		token_heredoc(last_file, file, tokens, env);
		tokens = tokens->next;
	}
	return (tokens->next);
}

void	parse_tokens_utils(t_file **file,
	t_token **tokens, t_file **last_file, t_cmd **cmd)
{
	t_cmd	*new_cmd;
	t_file	*new_file;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	new_file = ft_calloc(1, sizeof(t_file));
	if (!new_cmd || !new_file)
		return ;
	new_cmd->file = new_file;
	(*cmd)->next = new_cmd;
	*cmd = new_cmd;
	*tokens = (*tokens)->next;
	*file = new_file;
	*last_file = NULL;
}

t_cmd	*parse_tokens(t_token *tokens, t_env *env)
{
	t_all_data	data;

	data.file = ft_calloc(1, sizeof(t_file));
	data.cmd = ft_calloc(1, sizeof(t_cmd));
	if (!data.cmd || !data.file)
		return (NULL);
	data.start = data.cmd;
	data.cmd->file = data.file;
	data.last_file = NULL;
	while (tokens)
	{
		while (tokens && tokens->type != TOKEN_PIPE)
		{
			if (tokens->type == TOKEN_WORD)
				add_arg(data.cmd, tokens->value);
			tokens = parse_tokens_helper(tokens,
					&data.last_file, data.file, env);
			if (g_here_doc_helper == 20)
				return (NULL);
		}
		if (tokens && tokens->type == TOKEN_PIPE)
			parse_tokens_utils(&data.file, &tokens, &data.last_file, &data.cmd);
	}
	return (data.start);
}
