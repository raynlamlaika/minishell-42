/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expande_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 03:07:53 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/03 21:22:25 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_exits_s(int *exit_s, char *result, int *a, int *i)
{
	char	*ext_s;
	int		you;

	(void) exit_s;
	if (exit_status(0, 0) == NULL)
		ext_s = ft_strdup("0");
	else
		ext_s = ft_itoa(*exit_status(0, 0));
	you = 0;
	while (ext_s[you])
		result[(*a)++] = ext_s[you++];
	(*i)++;
}

char	*expaned_ed(char*string, t_env *env, int i)
{
	char	*tmp;

	tmp = ft_take(string, &i, env);
	if (!tmp)
	{
		env->emg_flag = 1;
		tmp = ft_strdup("");
	}
	if (tmp[0] == '\0')
		env->emg_flag = 1;
	return (tmp);
}
