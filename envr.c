/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:24:23 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/18 05:06:47 by rlamlaik         ###   ########.fr       */
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

char *get_value(t_env *linked_env, char *input)
{
	char	*value;
	int		i;

	i = ft_strlen(input) + 1;
	while (linked_env)
	{
		if (ft_strncmp(linked_env->key, input,i) == 0)
			break ;
		linked_env = linked_env->next;
	}
	value = input;
	return (value);
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
