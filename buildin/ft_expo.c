/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:36:15 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/26 15:54:13 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*take_key_exp(char*str, int j)
{
	int		i;
	char	*result;

	i = 0;
	if (j <= 0)
		return (NULL);
	if (!str)
		return (NULL);
	if (!str || !(is_valid_varname(ft_substr(str, 0, j))))
		return (NULL);
	result = ft_malloc((j + 1), 1);
	while (i < j)
	{
		result[i] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

int	f_size(char *str, int i)
{
	int	j;

	j = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
		j++;
	}
	return (j);
}

char	*takee_value(char *str, int pointed_to)
{
	char	*result;
	int		i;

	if (!str)
		return (NULL);
	result = ft_malloc((f_size(str, pointed_to) + 1), 1);
	i = 0;
	while (str[pointed_to])
		result[i++] = str[pointed_to++];
	result[i] = '\0';
	return (result);
}

t_env	*search_node(char *key, t_env *head)
{
	if (!head || !key)
		return (NULL);
	while (head)
	{
		if (!head->key)
			return (NULL);
		if (ft_strcmp(head->key, key) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

int	check_empty(char **args, int *i, int *j)
{
	int	flag;

	flag = 0;
	if (args[*i][0] == '\0')
	{
		fprintf(stderr, "minihel: export: `': not a valid identifier\n");
		flag = 1;
		return (flag);
	}
	if (ft_strlen(args[*i]) == 0)
	{
		fprintf(stderr, "export : `%c`: not a valid identifier\n", args[*i][*j]);
		(*i)++;
		flag = 1;
	}
	return (flag);
}
