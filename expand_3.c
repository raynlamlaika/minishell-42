/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:01:05 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/27 09:08:18 by rlamlaik         ###   ########.fr       */
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

void	helper(t_split *split, char *embg, t_token *token, char *result)
{
	t_token	*new_node;

	split->str[split->a] = '\0';
	if (split->add == 0)
	{
		token->value = ft_handel_qoute(split->str);
		token->ambiguous = ft_strdup(embg);
		split->add = 1;
	}
	else
	{
		new_node = create_token(split->str, embg);
		insert_token_after(token, new_node);
		token = new_node;
	}
	if (result[split->i])
	{
		split->size = split_alloc(result + split->i);
		split->str = ft_malloc(split->size + 1, 1);
	}
	
}

char	*s_split(char *result, t_token *token, char *embg)
{
	t_split	*split;

	split = ft_malloc(sizeof(t_split), 1);
	(1) && (split->a = 0, split->y = 0, split->i = 0, split->m = 0, \
split->i = 0, split->n = 0, split->add = 0, split->size = split_alloc(result));
	split->str = ft_malloc(split->size + 1, 1);
	while (result[split->i])
	{
		split->a = 0;
		while (result[split->i])
		{
			if (result[split->i] == '\"' && split->m % 2 == 0)
				(1) && (split->n++, split->y = split->n);
			if (result[split->i] == '\'' && split->n % 2 == 0)
				(1) && (split->m++, split->y = split->m);
			if (split->y % 2 != 0)
				split->str[split->a++] = result[split->i++];
			else
			{
				split->str[split->a++] = result[split->i++];
				if (result[split->i] == ' ')
				{
					while (result[split->i] == ' ')
						split->i++;
					break ;
				}
			}
		}
		helper(split, embg, token, result);
	}
	return (hendel_qoutes(result));
}
