/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:35:11 by abouabba          #+#    #+#             */
/*   Updated: 2025/05/29 17:20:28 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_arg(t_cmd *type, char *value)
{
	int		count;
	int		i;
	char	**new_args;

	count = 0;
	if (type->args)
	{
		while (type->args[count])
			count++;
	}
	new_args = ft_malloc(sizeof(char *) * (count + 2), 1);
	if (!new_args)
		return ;
	i = 0;
	while (i < count)
	{
		new_args[i] = ft_strdup(type->args[i]);
		i++;
	}
	new_args[count] = ft_strdup(value);
	new_args[count + 1] = NULL;
	type->args = new_args;
}

void	token_infile(t_file **last_file, t_file *file, t_token *tokens)
{
	t_file	*new_file;

	if (!*last_file)
	{
		file->infile = tokens->next->value;
		*last_file = file;
	}
	else
	{
		new_file = ft_calloc(1, sizeof(t_file));
		(*last_file)->next = new_file;
		*last_file = new_file;
		new_file->infile = tokens->next->value;
	}
}

void	token_outfile(t_file **last_file, t_file *file, t_token *tokens)
{
	t_file	*new_file;

	if (!*last_file)
	{
		file->outfile = tokens->next->value;
		file->append = 0;
		*last_file = file;
	}
	else
	{
		new_file = ft_calloc(1, sizeof(t_file));
		(*last_file)->next = new_file;
		*last_file = new_file;
		new_file->outfile = tokens->next->value;
		new_file->append = 0;
	}
}

void	token_append(t_file **last_file, t_file *file, t_token *tokens)
{
	t_file	*new_file;

	if (!*last_file)
	{
		file->outfile = tokens->next->value;
		file->append = 1;
		*last_file = file;
	}
	else
	{
		new_file = ft_calloc(1, sizeof(t_file));
		(*last_file)->next = new_file;
		*last_file = new_file;
		new_file->outfile = tokens->next->value;
		new_file->append = 1;
	}
}

void	token_heredoc(t_file **last_file,
	t_file *file, t_token *tokens, t_env *env)
{
	t_file	*new_file;

	if (!*last_file)
	{
		file->here_doc = heredoc(tokens->next->value, env, file);
		*last_file = file;
	}
	else
	{
		new_file = ft_calloc(1, sizeof(t_file));
		(*last_file)->next = new_file;
		*last_file = new_file;
		new_file->here_doc = heredoc(tokens->next->value, env, file);
	}
}
