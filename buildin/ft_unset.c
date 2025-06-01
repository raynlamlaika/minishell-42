/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:50:08 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/30 23:27:04 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_node(t_env **head, const char *key_to_remove)
{
	t_env	*curr;
	t_env	*prev;

	(1) && (prev = NULL, curr = *head);
	if (!head || !*head)
		return ;
	while (curr)
	{
		if (curr->key)
		{
			if (ft_strcmp(curr->key, key_to_remove) == 0)
			{
				exit_status(0, 1);
				if (prev)
					prev->next = curr->next;
				else
					*head = curr->next;
				(1) && (curr->key = NULL, curr->value = NULL, curr = NULL);
				return ;
			}
			(1) && (prev = curr, curr = curr->next);
		}
		else
			(1) && (curr->key = NULL, curr = NULL);
	}
}

void	ft_unset(char **args, t_env **env_list)
{
	int	i;

	i = 1;
	if (!*env_list)
		return ;
	while (args[i])
	{
		if (ft_strncmp(args[i], "_", 2) == 0)
			i++;
		else
		{
			remove_node(env_list, args[i]);
			i++;
		}
	}
}
