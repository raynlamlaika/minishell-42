/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:21:19 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/01 22:40:59 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_current_dir(t_env *env_list)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	env_list->pwd_d = ft_strdup(tmp);
	free (tmp);
}

void	ft_pwd(t_env *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	else if (env->pwd_d)
		printf("%s\n", env->pwd_d);
	else
		perror("pwd");
}
