/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 00:55:46 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/12 20:38:11 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *value, char *help_red)
{
	t_token	*new;

	new = NULL;
	new = ft_malloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	new->value = ft_strdup(ft_handel_qoute(value));
	new->type = TOKEN_WORD;
	if (help_red)
		new->ambiguous = ft_strdup(help_red);
	else
		new->ambiguous = NULL;
	new->next = NULL;
	return (new);
}

void	insert_token_after(t_token *current, t_token *new_node)
{
	new_node->next = current->next;
	current->next = new_node;
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

int	helper_valid(char *str, int export)
{
	if ((ft_strcmp("export", str) == 0 && export == 0) \
	&& ft_strrchr(str, '='))
		return (1);
	return (0);
}
