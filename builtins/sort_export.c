/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:48:13 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/18 19:25:33 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_new(char *key, char *value)
{
	t_env	*node;

	node = ft_malloc(sizeof(t_env), 1);
	if (!node)
		return (NULL);
	if (key != NULL)
		node->key = ft_strdup(key);
	else
		node->key = NULL;
	if (value != NULL)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

void	env_insert_sorted(t_env **sorted, t_env *new_node)
{
	t_env	*curr;

	if (!*sorted || ft_strcmp(new_node->key, (*sorted)->key) < 0)
	{
		new_node->next = *sorted;
		*sorted = new_node;
		return ;
	}
	curr = *sorted;
	while (curr->next && ft_strcmp(new_node->key, curr->next->key) > 0)
		curr = curr->next;
	new_node->next = curr->next;
	curr->next = new_node;
}

t_env	*sort_env(t_env *env)
{
	t_env	*sorted;
	t_env	*tmp;

	sorted = NULL;
	while (env)
	{
		tmp = env_new(env->key, env->value);
		if (!tmp)
			return (NULL);
		env_insert_sorted(&sorted, tmp);
		env = env->next;
	}
	return (sorted);
}

// void	ft_print_env(t_env *env)
// {
// 	if (!env)
// 		return ;
// 	env = sort_env(env);
// 	while (env)
// 	{
// 		if (env->key && ft_strcmp(env->key, "_"))
// 			print_error_arg("declare -x ", env->key, "");
// 		if (env->value && ft_strcmp(env->key, "_"))
// 			print_error_arg("=\"", env->value, "\"");
// 		if (env->key && ft_strcmp(env->key, "_"))
// 			putstr("\n");
// 		env = env->next;
// 		if (!env)
// 			break ;
// 	}
// 	return ;
// }

void	ft_print_env(t_env *env)
{
	char	*tmp;
	char	*line;

	if (!env)
		return ;

	env = sort_env(env);
	while (env)
	{
		if (env->key && ft_strcmp(env->key, "_") != 0)
		{
			if (env->value)
			{
				tmp = ft_strjoin("declare -x ", env->key);
				line = ft_strjoin(tmp, "=\"");
				tmp = ft_strjoin(line, env->value);
				line = ft_strjoin(tmp, "\"\n");
			}
			else
			{
				tmp = ft_strjoin("declare -x ", env->key);
				line = ft_strjoin(tmp, "\n");
			}
			write(1, line, ft_strlen(line));
		}
		env = env->next;
	}
}
