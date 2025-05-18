/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 23:45:50 by abouabba          #+#    #+#             */
/*   Updated: 2025/05/18 10:04:37 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_pwd(char *oldpwd, char *newpwd)
{
	if (oldpwd)
		setenv("OLDPWD", oldpwd, 1);
	else
		setenv("OLDPWD", "", 1);
	if (newpwd)
	{
		setenv("PWD", newpwd, 1);
		// free(newpwd);
	}
}

void	ft_cd_2(char *target, char *oldpwd, char *newpwd)
{
	char	*temp;
	int		len;
	char	*cwd;

	temp = NULL;
	len = 0;
	
	if (target[0] == '/')
		newpwd = strdup(target);
	else if (oldpwd)
	{
		len = strlen(oldpwd);
		if (oldpwd[len - 1] == '/')
			temp = ft_strdup(oldpwd);
		else
			temp = ft_strjoin(oldpwd, "/");
		newpwd = ft_strjoin(temp, target);
		// free(temp);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
    	perror("cd: error retrieving current directory");
	else
    	// free(cwd);

	update_pwd(oldpwd, newpwd);
}

char	*expnd_cd(char *input, t_env *env)
{
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
void	ft_cd(char **args, t_env *env)
{
	char	*oldpwd;
	char	*newpwd;
	char	*target;

	newpwd = NULL;
	oldpwd = expnd_cd("PWD", env);
	if (!oldpwd)
		return ;
	if (!args[1] || strcmp(args[1], "~") == 0)
	{
		target = expnd_cd("HOME", env);
		if (!target)
		{
			printf("cd: HOME not set\n");
			return ;
		}
	}
	else
		target = args[1];
	if (chdir(target) != 0)
	{
		perror("cd");
		return ;
	}
	ft_cd_2(target, oldpwd, newpwd);
}