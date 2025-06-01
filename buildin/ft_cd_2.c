/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:27:45 by abouabba          #+#    #+#             */
/*   Updated: 2025/06/01 13:35:20 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*expnd_cd(char *input, t_env *env)
{
	if (!env || !env->key)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(input, env->key) == 0)
			return (env->value);
		env = env->next;
		if (!env)
			return (NULL);
	}
	return (NULL);
}

void	update_env_value(char *key, char *value, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
}

void	update_pwd(char *oldpwd, char *newpwd, t_env *env)
{
	if (oldpwd)
		update_env_value("OLDPWD", oldpwd, env);
	else
		update_env_value("OLDPWD", "", env);
	if (newpwd)
	{
		update_env_value("PWD", newpwd, env);
	}
}

char	*add_dotdot_to_pwd(char *pwd, char *target)
{
	char	*newpwd;
	char	*temp;

	if (!pwd)
		return (target);
	if (pwd[ft_strlen(pwd) - 1] == '/')
		newpwd = ft_strjoin(pwd, target);
	else
	{
		temp = ft_strjoin(pwd, "/");
		newpwd = ft_strjoin(temp, target);
	}
	return (newpwd);
}
