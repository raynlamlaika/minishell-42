/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 23:45:50 by abouabba          #+#    #+#             */
/*   Updated: 2025/05/15 16:05:22 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
char	*ft_strjoinnn(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s_everyone;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s_everyone
		= (char *)malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!s_everyone)
		return (NULL);
	while (s1[i])
	{
		s_everyone[i] = s1[i];
		i++;
	}
	while (s2[j])
		s_everyone[i++] = s2[j++];
	s_everyone[i] = '\0';
	return (s_everyone);
}

char	*ft_strduppp(char*source)
{
	size_t	o;
	char	*sp;

	o = 0;
	sp = (char *) malloc((ft_strlen(source) + 1) * sizeof(char));
	if (!sp)
		return (NULL);
	while (source[o])
	{
		sp[o] = source[o];
		o++;
	}
	sp[o] = '\0';
	return (sp);
}

void	update_pwd(char *oldpwd, char *newpwd)
{
	if (oldpwd)
		setenv("OLDPWD", oldpwd, 1);
	else
		setenv("OLDPWD", "", 1);
	if (newpwd)
	{
		setenv("PWD", newpwd, 1);
		free(newpwd);
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
			temp = ft_strduppp(oldpwd);
		else
			temp = ft_strjoinnn(oldpwd, "/");
		newpwd = ft_strjoinnn(temp, target);
		free(temp);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
    	perror("cd: error retrieving current directory");
	else
    	free(cwd);

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