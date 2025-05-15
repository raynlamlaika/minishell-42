/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 00:55:46 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/15 11:48:11 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *value)
{
	t_token	*new;

	new = NULL;
	new = ft_malloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	new->value = ft_strdup(ft_handel_qoute(value));
	new->type = TOKEN_WORD;
	new->next = NULL;
	return (new);
}

void	insert_token_after(t_token *current, t_token *new_token)
{
	t_token	*old_next;

	if (!current || !new_token)
		return ;
	old_next = current->next;
	current->next = new_token;
	new_token->next = old_next;
}

char	*ft_replace(char *check, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, check) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}
