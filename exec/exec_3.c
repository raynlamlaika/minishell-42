/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:00:30 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/01 15:55:47 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	take_child(t_cmd *full, char **path, int *exit_s, t_env **env)
{
	char	*pathh;
	char	**cmd;

	cmd = full->args;
	if (search_search(cmd[0]) == 1)
	{
		buildin(full, env, exit_s);
		ft_malloc(0, 0);
		exit(*exit_s);
	}
	
	else
	{
		pathh = pick(path, cmd[0]);
		if (!pathh)
			path_null(cmd[0]);
		if (!(*env)->env_v)
			execve(pathh, cmd, NULL);
		if (cmd[0][0] == '\0')
			null_cmd(cmd[0]);
		else
			ft_exec(pathh, env, cmd);
		ft_malloc(0, 0);
		exit(126);
	}
}

void	save_exit_s(int count, int *exit_s)
{
	int	status;
	int	exit_status;

	while (count > 0)
	{
		wait(&status);
		count--;
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			*exit_s = exit_status;
		}
	}
}

void	execute_child_process(t_cmd *full, t_context *ctx)
{
	exectution_helper(ctx->exec, full, ctx->perv_pipe);
	if (full->args && ctx->exec->inf != -5 && ctx->exec->outf != -5)
		take_child(full, ctx->exec->path, ctx->exit_s, ctx->env);
	else if (!full->args)
	{
		close_helper(ctx->exec->inf, \
full, ctx->exec->pipefd, ctx->perv_pipe);
		if (ctx->exec->outf > 0)
			close(ctx->exec->outf);
		exit(0);
	}
}
