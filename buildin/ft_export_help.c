/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:32:16 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/27 03:27:54 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_print_env(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		if (env->key)
			printf("declare -x %s", env->key);
		if (env->value)
			printf("=\"%s\"", env->value);
		if (env->key)
			printf("\n");
		env = env->next;
		if (!env)
			break ;
	}
	return ;
}

void	add_to_env_list(t_env **env_list, t_env *new_node)
{
	t_env	*last;

	if (!*env_list)
	{
		*env_list = new_node;
		return ;
	}
	last = *env_list;
	while (last->next)
		last = last->next;
	last->next = new_node;
}

t_env	*creat_node_env(char *key, char *value)
{
	t_env	*new;

	new = ft_malloc(sizeof(t_env), 1);
	new->key = key;
	new->value = value;
	return (new);
}

int	is_valid_varname(char *name)
{
	int	i;

	i = 1;
	if ((!name || !ft_isalpha(name[0])) && name[0] != '_')
	{
		fprintf(stderr, "export : `%c`: not a valid identifier\n", name[0]);
		return (0);
	}
	while (name[i])
	{
		if (!isalnum(name[i]) && name[i] != '_')
		{
			fprintf(stderr, "export : `%c`: not a valid identifier\n", name[i]);
			return (0);
		}
		i++;
	}
	return (1);
}
