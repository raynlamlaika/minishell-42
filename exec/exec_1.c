/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:22:42 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/01 13:06:51 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	path_null(char*arg)
{
	fprintf(stderr, "minishell:%s : command not found\n", arg);
	ft_malloc(0, 0);
	exit(127);
}

void	null_cmd(char*arg)
{
	fprintf(stderr, "minishell:%s : command not found\n", arg);
	ft_malloc(0, 0);
	exit(127);
}

void	ft_exec(char *pathh, t_env **env, char	**cmd)
{
	execve(pathh, cmd, (*env)->env_v);
	perror("execve failed");
}
