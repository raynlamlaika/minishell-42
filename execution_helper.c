/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:11:01 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/26 14:16:12 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command_s(t_finished *helper, int *exit_s)
{
	char	**path;

	path = takepaths(&helper->env);
	helper->bin = pick(path, helper->args[0]);
	if (!helper->bin && helper->args[0][0] != '\0')
	{
		execve(helper->args[0], helper->args, helper->env->env_v);
		if (ft_strrchr(helper->args[0], '$') == NULL)
			fprintf(stderr, "%s: command not found\n", helper->args[0]);
		*exit_s = 127;
		ft_malloc(0, 0);
		exit(*exit_s);
	}
	if (helper->args[0][0] == '\0')
	{
		fprintf(stderr, "minishell: : command not found\n");
		ft_malloc(0, 0);
		exit(127);
	}
	if (!helper->env->env_v)
		execve(helper->bin, helper->args, NULL);
	execve(helper->bin, helper->args, helper->env->env_v);
	fprintf(stderr, "%s: command not found\n", helper->args[0]);
	ft_malloc(0, 0);
	exit(126);
}

void	handle_redirections(int inf, int outf)
{
	if (inf > -1)
	{
		dup2(inf, STDIN_FILENO);
		close(inf);
	}
	if (outf > -1)
	{
		dup2(outf, STDOUT_FILENO);
		close(outf);
	}
}

void	execute_forked_cmd(t_finished *helper, int *exit_s, int *status)
{
	pid_t	pid;

	pid = fork();
	here_doc_helper = 1337;
	signal(SIGQUIT, handle_signal);
	if (pid == -1)
	{
		fprintf(stderr, "minishell: `fork' failed to create a Child\n");
		ft_malloc(0, 0);
		return ;
	}
	if (pid == 0)
	{
		handle_redirections(helper->inf, helper->outf);
		if (helper->inf != -5 && helper->outf != -5)
			execute_command_s(helper, exit_s);
	}
	else
		waitpid(pid, status, 0);
}

void	exectution_helper(int inf, int outf, int *pipefd, t_cmd *full, int perv_pipe)
{
	struct stat stat_in, stat_stdin, stat_out, stat_stdout;

	get_redirections(&inf, &outf, full);
	if (inf > -1 &&
		fstat(inf, &stat_in) == 0 &&
		fstat(STDIN_FILENO, &stat_stdin) == 0 &&
		!(stat_in.st_ino == stat_stdin.st_ino && stat_in.st_dev == stat_stdin.st_dev))
	{
		dup2(inf, STDIN_FILENO);
		close(inf);
	}
	else if (perv_pipe != -1)
		dup2(perv_pipe, STDIN_FILENO);
	if (outf > -1 &&
		fstat(outf, &stat_out) == 0 &&
		fstat(STDOUT_FILENO, &stat_stdout) == 0 &&
		!(stat_out.st_ino == stat_stdout.st_ino && stat_out.st_dev == stat_stdout.st_dev))
		(1) && (dup2(outf, STDOUT_FILENO), close(outf));
	else if (full->next)			
		dup2(pipefd[1], STDOUT_FILENO);
	(1) && (close(pipefd[0]), close(pipefd[1]));
}

void	close_helper(int inf, int outf, t_cmd *full, int *pipefd, int perv_pipe)
{
	if (inf > 0)
		close(inf);
	if (outf > 0)
		close(outf);
	if(full->file->here_doc > 0)
		close(full->file->here_doc);
	handelprevpipe(pipefd, &perv_pipe);
}
