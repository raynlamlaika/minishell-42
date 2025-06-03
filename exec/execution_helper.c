/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:11:01 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/03 14:42:36 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_forked_cmd(t_finished *helper, int *exit_s, int *status)
{
	pid_t	pid;
	int		signal_h;
	int		exit_status;

	(1) && (signal_h = 0, pid = fork());
	if (pid == -1)
	{
		printf_error("minishell: `fork' failed to create a Child\n");
		return ((void)ft_malloc(0, 0));
	}
	if (pid == 0)
	{
		g_here_doc_helper = 133;
		signal(SIGQUIT, handle_signal);
		handle_redirections(helper->inf, helper->outf);
		if (helper->inf != -5 && helper->outf != -5)
			execute_command_s(helper, exit_s);
	}
	else
		waitpid(pid, status, 0);
	if (WIFSIGNALED(*status) && signal_h == 0)
		(write(2, "\n", 2), signal_h++);
	else if (WIFEXITED(*status))
		(1) && (exit_status = WEXITSTATUS(*status), *exit_s = exit_status);
}

void	exectution_helper(t_exec *exec, t_cmd *full, int perv_pipe)
{
	t_stat	stat;

	get_redirections(&exec->inf, &exec->outf, full);
	if (exec->inf == -5 || exec->outf == -5)
		exit(1);
	if (exec->inf > -1 && fstat(exec->inf, \
	&stat.stat_in) == 0 && fstat(STDIN_FILENO, &stat.stat_stdin) \
	== 0 && !(stat.stat_in.st_ino == stat.stat_stdin.st_ino \
	&& stat.stat_in.st_dev == stat.stat_stdin.st_dev))
	{
		dup2(exec->inf, STDIN_FILENO);
		close(exec->inf);
	}
	else if (perv_pipe != -1)
		dup2(perv_pipe, STDIN_FILENO);
	if (exec->outf > -1 && fstat(exec->outf, \
&stat.stat_out) == 0 && fstat(STDOUT_FILENO, &stat.stat_stdout) \
	== 0 &&!(stat.stat_out.st_ino == stat.stat_stdout.st_ino \
	&& stat.stat_out.st_dev == stat.stat_stdout.st_dev))
		(1) && (dup2(exec->outf, STDOUT_FILENO), close(exec->outf));
	else if (full->next)
		dup2(exec->pipefd[1], STDOUT_FILENO);
	(1) && (close(exec->pipefd[0]), close(exec->pipefd[1]));
}

void	close_helper(int inf, t_cmd *full, int *pipefd, int perv_pipe)
{
	if (inf > 0)
		close(inf);
	if (full->file->here_doc > 0)
		close(full->file->here_doc);
	handelprevpipe(pipefd, &perv_pipe);
}
