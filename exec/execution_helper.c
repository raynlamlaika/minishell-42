/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:11:01 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/01 23:17:02 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_forked_cmd(t_finished *helper, int *exit_s, int *status)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		fprintf(stderr, "minishell: `fork' failed to create a Child\n");
		ft_malloc(0, 0);
		return ;
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
}

void	exectution_helper(t_exec *exec, t_cmd *full, int perv_pipe)
{
	struct stat	stat_in, stat_stdin, stat_out, stat_stdout;

	get_redirections(&exec->inf, &exec->outf, full);
	if (exec->inf == -5 || exec->outf == -5)
		exit(1);
	if (exec->inf > -1 && fstat(exec->inf, \
	&stat_in) == 0 && fstat(STDIN_FILENO, &stat_stdin) \
 == 0 && !(stat_in.st_ino == stat_stdin.st_ino \
&& stat_in.st_dev == stat_stdin.st_dev))
	{
		dup2(exec->inf, STDIN_FILENO);
		close(exec->inf);
	}
	else if (perv_pipe != -1)
		dup2(perv_pipe, STDIN_FILENO);
	if (exec->outf > -1 &&
		fstat(exec->outf, &stat_out) == 0 &&
		fstat(STDOUT_FILENO, &stat_stdout) \
	== 0 &&!(stat_out.st_ino == stat_stdout.st_ino \
	&& stat_out.st_dev == stat_stdout.st_dev))
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
