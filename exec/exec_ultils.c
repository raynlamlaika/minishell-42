/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ultils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:49:18 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/27 02:09:35 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **takepaths(t_env **env)
{
	char	**path;
	char	*take;
	int		enc;
	t_env *env_lnk;

	1 && (take = NULL, env_lnk = *env);
	if (!env_lnk || !env_lnk->key)
		return (NULL);
	while (env_lnk)
	{
		if (ft_strcmp(env_lnk->key,"PATH") == 0)
		{
			take = ft_strdup(env_lnk->value);
			break ;
		}
		env_lnk = env_lnk->next;
	}
	if (!take)
		return (NULL);
	(1) && (path = ft_split(take, ':'), enc = 0);
	while (path[enc])
	{
		path[enc] = ft_strjoin(path[enc], "/");
		enc++;
	}
	return (path);
}

char	*pick(char**path, char*cmd)
{
	int		pass;
	char	*realpath;
	char	**cmdpath;

	pass = 0;
	if (ft_strrchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
		{
			cmdpath = ft_split(cmd, ' ');
			return (cmdpath[0]);
		}
		return (NULL);
	}
	if (!path)
		return (NULL);
	while (path[pass])
	{
		realpath = ft_strjoin(path[pass], cmd);
		if (access(realpath, X_OK) == 0)
			return (realpath);

		pass++;
	}
	return (NULL);
}

