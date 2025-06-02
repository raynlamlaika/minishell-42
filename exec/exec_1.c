/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:22:42 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/02 08:03:10 by abouabba         ###   ########.fr       */
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

void	ft_exec(char *pathh, t_env **env, char	**cmd)
{
	execve(pathh, cmd, (*env)->env_v);
	perror("execve failed");
}
