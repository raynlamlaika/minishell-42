/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 23:45:50 by abouabba          #+#    #+#             */
/*   Updated: 2025/05/19 14:27:52 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strduppp(char*source)
{
	size_t	o;
	char	*sp;

	o = 0;
	sp = (char *)malloc((ft_strlen(source) + 1) * sizeof(char));
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
		return (ft_strduppp(s2));
	if (!s2)
		return (ft_strduppp(s1));
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
	t_env *tmp = env;

	if (!env || !env->key)
		return ;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			// free(tmp->value);
			tmp->value =NULL;
			tmp->value = ft_strdup(value);
			return;
		}
		tmp = tmp->next;
	}
	t_env *new_node = ft_malloc(sizeof(t_env), 1);
	if (!new_node)
		return;
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (!env)
		env = new_node;
	else
	{
		tmp = env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
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
		newpwd = NULL;
		// free(newpwd);
	}
}

char	*add_dotdot_to_pwd(char *pwd, char *target)
{
	char *newpwd;

	if (!pwd)
		return ft_strdup(target);

	if (pwd[ft_strlen(pwd) - 1] == '/')
		newpwd = ft_strjoin(pwd, target);
	else
	{
		char *temp = ft_strjoin(pwd, "/");
		newpwd = ft_strjoin(temp, target);
		free(temp);
	}
	return (newpwd);
}

void	ft_cd(char **args, t_env *env)
{
	char	*oldpwd;
	char	*newpwd;
	char	*target;

	oldpwd = expnd_cd("PWD", env);
	
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
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

	if (!oldpwd)
		oldpwd = getcwd(NULL, 0);
	if (chdir(target) != 0)
	{
		perror("cd");
		free(oldpwd);
		return;
	}
	
	newpwd = getcwd(NULL, 0);

	if (!newpwd)
	{
		perror("cd: error retrieving current directory");
		newpwd = add_dotdot_to_pwd(oldpwd, target);
	}

	update_pwd(oldpwd, newpwd, env);
	free(newpwd);
}
