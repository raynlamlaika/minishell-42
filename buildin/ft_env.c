/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:06:42 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/02 01:00:40 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**env_arr(t_env *env)
{
	char	**array;
	int		size;
	int		len;
	int		i;

	if (!env)
		return (NULL);
	(1) && (size = env_list_size(env), i = 0);
	array = ft_malloc(sizeof(char *) * (size + 1), 1);
	if (!array)
		return (NULL);
	while (env)
	{
		if (env->key && env->value)
		{
			len = strlen(env->key) + strlen(env->value) + 2;
			array[i] = ft_malloc(len, 1);
			if (!array[i])
				return (NULL);
			i++;
		}
		env = env->next;
	}
	return (array[i] = NULL, array);
}

void	ft_env(t_env *env)
{
	while (env)
	{
		if (env->key && env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
