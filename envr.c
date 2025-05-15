/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:24:23 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/15 16:59:27 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char *handling_qoutes(char *word, char sepa)
{
	int i = 0;
	int count = 0;
	char *result;
	int j = 0;
	
	while (word[i])
	{
		if (word[i] != sepa)
			count++;
		i++;
	}
	result = ft_malloc(count + 1, 1);
	if (!result)
		return NULL;

	i = 0;

	while (word[i])
	{
		if (word[i] != sepa)
		{
			result[j] = word[i];
			j++;
		}
		i++;
	}

	result[j] = '\0';
	return (result);
}

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

	if (!env || !*env)
		return (NULL);
	while (env[j])
	{
		int i = 0;
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

char *get_value(t_env *linked_env, char *input)
{
	char *value;
	int i;

	i = ft_strlen(input) + 1;
	while (linked_env)
	{
		if (ft_strncmp(linked_env->key, input,i) == 0)
		{
			printf("this is the VALUE :%s\n", linked_env->value);
			break ;
		}
		linked_env = linked_env->next;
	}
	value = input;
	return (value);
}

void print_env_list(t_env *head)
{
	while (head)
	{
		printf("KEY: %-20s | VALUE: %s\n", head->key, head->value);
		head = head->next;
	}
}

void	free_env_list(t_env *head)
{
	t_env *tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
