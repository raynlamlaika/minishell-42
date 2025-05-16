/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_heloper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:08:52 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/15 21:09:04 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *take_key(char **env, int i, int j)
{
	char *key = malloc(i + 1);
	if (!key) return NULL;
	strncpy(key, env[j], i);
	key[i] = '\0';
	return key;
}

char *take_value(char **env, int i, int j)
{
	i++;
	int len = strlen(env[j] + i);
	char *value = malloc(len + 1);
	if (!value) return NULL;
	strcpy(value, env[j] + i);
	return value;
}

t_env *new_node(char *key, char *value)
{
	t_env *node = malloc(sizeof(t_env));
	if (!node) return NULL;
	node->key = key;
	node->value = value;
	node->next = NULL;
	return node;
}

void append_node(t_env **head, t_env *new)
{
	if (!*head)
		*head = new;
	else {
		t_env *tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_env *linked_varibles(char **env)
{
	t_env *head = NULL;
	int j = 0;
	int i;

	if (!env || !*env)
		return (NULL);
	while (env[j])
	{
		i = 0;
		while (env[j][i])
		{
			if (env[j][i] == '=')
			{
				char *key = take_key(env, i, j);
				char *value = take_value(env, i, j);
				append_node(&head, new_node(key, value));
				break;
			}
			i++;
		}
		j++;
	}
	
	head->env_v = env;
	return (head);
}
