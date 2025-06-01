/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 23:45:50 by abouabba          #+#    #+#             */
/*   Updated: 2025/06/01 22:45:22 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_args(char **args)
{
	if (args[1] && args[2])
	{
		fprintf(stderr, "cd: too many arguments\n");
		exit_status(1, 1);
		return (1);
	}
	return (0);
}

static char	*get_target(char **args, t_env *env)
{
	char	*target;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		target = expnd_cd("HOME", env);
		if (!target)
			printf_error("cd: HOME not set\n");
		exit_status(1, 1);
		return (target);
	}
	return (args[1]);
}

static char	*get_safe_pwd(char *old_pwd, char *target, int *check__)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("cd: error retrieving current directory");
		*check__ = 1;
		exit_status(1, 1);
		return (add_dotdot_to_pwd(old_pwd, target));
	}
	return (pwd);
}

void	ft_cd(char **args, t_env *env)
{
	char	*newpwd;
	char	*target;
	int		check__;

	check__ = 0;
	if (check_args(args))
		return ;
	target = get_target(args, env);
	if (!target)
		return ;
	if (!env->pwd_d)
		env->pwd_d = getcwd(NULL, 0);
	if (chdir(target) != 0)
	{
		perror("minishell :cd");
		exit_status(1, 1);
		return ;
	}
	newpwd = get_safe_pwd(env->pwd_d, target, &check__);
	update_pwd(env->pwd_d, newpwd, env);
	env->pwd_d = ft_strdup(newpwd);
	if (!check__)
		free(newpwd);
}
