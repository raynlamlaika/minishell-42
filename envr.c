/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:24:23 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/24 14:08:48 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*handling_qoutes(char *word, char sepa)
{
	char	*result;
	int		i;
	int		count;
	int		j;

	(1) && (j = 0, count = 0, i = 0);
	while (word[i])
	{
		if (word[i] != sepa)
			count++;
		i++;
	}
	(1) && (i = 0, result = ft_malloc(count + 1, 1));
	if (!result)
		return (NULL);
	while (word[i])
	{
		if (word[i] != sepa)
		{
			result[j] = word[i];
			j++;
		}
		i++;
	}
	return (result[j] = '\0', result);
}

char	*get_value(t_env *linked_env, char *input)
{
	char	*value;
	int		i;

	i = ft_strlen(input) + 1;
	while (linked_env)
	{
		if (ft_strncmp(linked_env->key, input, i) == 0)
			break ;
		linked_env = linked_env->next;
	}
	value = input;
	return (value);
}

void	free_env_list(t_env *head)
{
	t_env	*tmp;

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
