/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:22:42 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/11 15:50:21 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	path_null(char*arg)
{
	print_error_arg("minishell:", arg, " : command not found\n");
	ft_malloc(0, 0);
	exit(127);
}

void	null_cmd(char*arg)
{
	print_error_arg("minishell:", arg, " : command not found\n");
	ft_malloc(0, 0);
	exit(127);
}

int	helper_sss(char *helper)
{
	struct stat	sb;

	if (!helper)
		return (1);
	if (ft_strchr(helper, '/'))
	{
		if (stat(helper, &sb) == 0)
		{
			if (S_ISDIR(sb.st_mode))
			{
				print_error_arg("minishell: ", helper, \
					": Is a directory\n");
				ft_malloc(0, 0);
				exit(126);
			}
		}
		else
			print_error_arg("", helper, \
				" : command not found\n");
	}
	else
		print_error_arg("minishell ", helper, \
			":No such file or directory \n");
	ft_malloc(0, 0);
	exit(127);
}

void	ft_exec(char *pathh, t_env **env, char	**cmd)
{
	execve(pathh, cmd, (*env)->env_v);
	helper_sss(cmd[0]);
}
