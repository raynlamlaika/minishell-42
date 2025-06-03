/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updat_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:07:09 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/03 02:47:22 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_up(t_export *expo, t_env **env)
{
	t_env	*new;

	if (ft_strcmp(expo->key, "_") != 0)
	{
		new = new_node(expo->key, expo->value);
		append_node(env, new);
	}
}

void	helper_d(t_env	*existing, t_export *expo, t_env **env)
{
	t_env	*new;
	char	*o;

	if (!existing)
	{
		if (ft_strcmp(expo->key, "_") != 0)
		{
			new = new_node(expo->key, NULL);
			append_node(env, new);
		}
	}
	else
	{
		if (ft_strcmp(expo->key, "_") != 0)
		{
			o = ft_strjoin(existing->value, expo->value);
			existing->value = o;
		}
	}
}

void	update_environment(t_export *expo, t_env **env)
{
	t_env	*existing;

	existing = search_node(expo->key, *env);
	if (existing && expo->flag == 0)
	{
		if ((ft_strcmp(expo->key, "_") != 0) && expo->value)
			existing->value = expo->value;
	}
	else if (expo->flag && expo->key)
		helper_d(existing, expo, env);
	else
		update_up(expo, env);
}
