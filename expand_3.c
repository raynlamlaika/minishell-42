/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:01:05 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/19 19:13:45 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_alloc(char *result)
{
	int	size;
	int	i;
	int	n;
	int	m;
	int	y;

	(1) && (size = 0, i = 0, n = 0, m = 0, y = 0);
	while (result[i])
	{
		if (result[i] == '\"' && m % 2 == 0)
			(1) && (n++, y = n);
		if (result[i] == '\'' && n % 2 == 0)
		{
			m++;
			y = m;
		}
		(1) && (size++, i++);
		if (y % 2 == 0 && result[i] == ' ')
		{
			while (result[i] == ' ')
				i++;
			break ;
		}
	}
	return (size);
}

void	helper(t_split *split, char *embg, t_token **token, char *result)
{
	t_token	*new_node;

	split->str[split->a] = '\0';
	if (split->add == 0)
	{
		(*token)->value = ft_handel_qoute(split->str);
		(*token)->ambiguous = ft_strdup(embg);
		split->add = 1;
	}
	else
	{
		new_node = create_token(split->str, embg);
		insert_token_after(*token, new_node);
		*token = new_node;
	}
	if (result[split->i])
	{
		split->size = split_alloc(result + split->i);
		split->str = ft_malloc(split->size + 1, 1);
	}
}

void	loop_spliting(t_split *split, char *result, t_token *token)
{
	while (result[split->i])
	{
		while (result[split->i] == ' ')
			split->i++;
		split->a = 0;
		split->y = 0;
		while (result[split->i])
		{
			if (result[split->i] == '\"' && split->m % 2 == 0)
				(1) && (split->n++, split->y = split->n);
			else if (result[split->i] == '\'' && split->n % 2 == 0)
				(1) && (split->m++, split->y = split->m);
			split->str[split->a++] = result[split->i++];
			if ((split->y % 2 == 0) && result[split->i] == ' ')
			{
				while (result[split->i] == ' ')
					split->i++;
				break ;
			}
		}
		split->str[split->a] = '\0';
		helper(split, split->embg, &token, result);
	}
}

char	*s_split(char *result, t_token *token, char *embg)
{
	t_split	*split;
	char	*re;

	split = ft_malloc(sizeof(t_split), 1);
	(1) && (split->a = 0, split->y = 0, split->i = 0, split->m = 0, \
split->i = 0, split->n = 0, split->add = 0, split->size = split_alloc(result));
	split->embg = ft_strdup(embg);
	split->str = ft_malloc(split->size + 1, 1);
	loop_spliting(split, result, token);
	re = hendel_qoutes(result);
	restore_hidden_q(re);
	return (re);
}
