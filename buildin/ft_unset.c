/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:50:08 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/25 16:51:42 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_node(t_env **head, const char *key_to_remove)
{
	t_env	*current;
	t_env	*prev;

	(1) && (prev = NULL, current = *head);
	if (!head || !*head)
		return ;
	while (current)
	{
		if (current->key)
		{
			if (ft_strcmp(current->key, key_to_remove) == 0)
			{
				if (prev)
					prev->next = current->next;
				else
					*head = current->next;
				(1) && (current->key = NULL, current->value = NULL);
				current = NULL;
				return ;
			}
			(1) && (prev = current, current = current->next);
		}
		else
			(1) && (current->key = NULL, current = NULL);
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
