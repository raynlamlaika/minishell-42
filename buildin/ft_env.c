/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:06:42 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/18 02:29:50 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	env_list_size(t_env *env)
// {
// 	int	count;

// 	count = 0;
// 	while (env != NULL)
// 	{
// 		count++;
// 		env = env->next;
// 	}
// 	return (count);
// }

// char	**env_arr(t_env *env)
// {
// 	char	**array;
// 	int		size;
// 	int		len;
// 	int		i;

// 	i = 0;
// 	if (!env || !env->key)
// 		return (NULL);
// 	size = env_list_size(env);
// 	array = ft_malloc(sizeof(char *) * (size + 1), 1);
// 	if (!array)
// 		return (NULL);
// 	while (env != NULL)
// 	{
// 		len = strlen(env->key) + strlen(env->value) + 4;
// 		array[i] = ft_malloc(len, 1);
// 		if (!array[i])
// 			return (NULL);
// 		i++;
// 		env = env->next;
// 	}
// 	array[i] = NULL;
// 	return (array);
// }

// char	**ft_env(t_env *env)
// {
// 	if (!env || !env->key)
// 		return (NULL);
// 	while (env)
// 	{
// 		printf("%s", env->key);
// 		if (env->value)
// 			printf("=%s\n", env->value);
// 		else
// 			printf("\n");
// 		env = env->next;
// 		if (!env)
// 			break ;
// 	}
// 	return (env_arr(env));
// }

int	env_list_size(t_env *env)
{
	int	count = 0;
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
	int		i = 0;

	if (!env)
		return (NULL);

	size = env_list_size(env);
	array = ft_malloc(sizeof(char *) * (size + 1), 1); // +1 for NULL terminator
	if (!array)
		return (NULL);

	while (env)
	{
		if (env->key && env->value)
		{
			len = strlen(env->key) + strlen(env->value) + 2; // '=' and '\0'
			array[i] = ft_malloc(len, 1);
			if (!array[i])
				return (NULL); // optional: free previously allocated ones
			snprintf(array[i], len, "%s=%s", env->key, env->value);
			i++;
		}
		env = env->next;
	}
	array[i] = NULL;
	return (array);
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
