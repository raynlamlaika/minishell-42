/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:45:49 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/01 23:15:19 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_parent_process(t_cmd *full, t_context *ctx, int *count)
{
	close_helper(ctx->exec->inf, \
full, ctx->exec->pipefd, ctx->perv_pipe);
	if (full->file->here_doc > 0)
		close(full->file->here_doc);
	if (ctx->exec->outf > 0)
		close(ctx->exec->outf);
	handelprevpipe(ctx->exec->pipefd, &ctx->perv_pipe);
	(*count)++;
}

void	execute_multiple_cmds(t_cmd *full, t_env **env, \
t_exec *exec, int *count)
{
	pid_t		pid;
	t_context	ctx;

	ctx.env = env;
	ctx.exit_s = exit_status(0, 0);
	ctx.exec = exec;
	ctx.perv_pipe = -1;
	while (full)
	{
		pipecheck(exec->pipefd);
		pid = fork();
		if (forkfaild(pid, exec->pipefd))
		{
			ft_malloc(0, 0);
			exit(128);
		}
		if (pid == 0)
		{
			g_here_doc_helper = 133;
			signal(SIGQUIT, handle_signal);
			execute_child_process(full, &ctx);
		}
		else
			execute_parent_process(full, &ctx, count);
		full = full->next;
	}
}

void	exectution(t_cmd *full, t_env **env, int *exit_s)
{
	int		count;
	t_exec	*exec;

	count = 0;
	exec = ft_malloc(sizeof(t_exec), 1);
	(1) && (exec->path = takepaths(env), exec->inf = 0, exec->outf = 0);
	exec->count = 0;
	if (full->next)
	{
		execute_multiple_cmds(full, env, exec, &count);
		close(exec->pipefd[0]);
		save_exit_s(count, exit_s);
	}
	else
		execute_single_cmd(full, env, exit_s);
}
