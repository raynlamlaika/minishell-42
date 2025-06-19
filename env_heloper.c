/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_heloper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:08:52 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/19 11:06:45 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_key(char **env, int i, int j)
{
	char	*key;

	key = ft_malloc(i + 1, 1);
	if (!key)
		return (NULL);
	ft_strncpy(key, env[j], i);
	key[i] = '\0';
	return (key);
}

char	*take_value(char **env, int i, int j)
{
	int		len;
	char	*value;

	i++;
	len = ft_strlen(env[j] + i);
	value = ft_malloc(len + 1, 1);
	if (!value)
		return (NULL);
	ft_strcpy(value, env[j] + i);
	return (value);
}

t_env	*new_node(char *key, char *value)
{
	t_env	*node;

	node = ft_malloc(sizeof(t_env), 1);
	if (!node)
		return (NULL);
	if (key)
		node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

int	append_node(t_env **head, t_env *new)
{
	t_env	*tmp;

	if (!*head || !head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

t_env	*linked_varibles(char **env)
{
	t_env	*head;
	char	*value;
	char	*key;
	int		j;
	int		i;

	(1) && (j = 0, head = NULL);
	if (!env || !*env)
		return (null_helper(head));
	while (env[j])
	{
		i = 0;
		while (env[j][i])
		{
			if (env[j][i] == '=')
			{
				(1) && (value = take_value(env, i, j), \
key = take_key(env, i, j), i = append_node(&head, new_node(key, value)));
				break ;
			}
			i++;
		}
		j++;
	}
	return (head->env_v = env, head);
}
