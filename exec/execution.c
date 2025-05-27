/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:45:49 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/27 10:26:25 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize_helper(t_finished *helper, t_cmd *cmd, t_env **env)
{
	helper->cmd = cmd;
	helper->env = *env;
	helper->args = cmd->args;
	get_redirections(&helper->inf, &helper->outf, cmd);
	helper->bin = NULL;
}

void	execute_single_cmd(t_cmd *cmd, t_env **env, int *exit_s)
{
	t_finished	*helper;
	int			status;
	int			saved_stdin;
	int			saved_stdout;

	status = 0;
	helper = ft_malloc(sizeof(t_finished), 1);
	initialize_helper(helper, cmd, env);
	if (!helper->args || !helper->args[0])
	{
		if (helper->inf > 0)
			close(helper->inf);
		if (helper->outf > 0)
			close(helper->outf);
		return ;
	}
	if (search_search(helper->args[0]) == 1)
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		if (helper->inf != -1)
			(1) && (dup2(helper->inf, STDIN_FILENO), close(helper->inf));
		if (helper->outf != -1)
			(1) && (dup2(helper->outf, STDOUT_FILENO), close(helper->outf));
		buildin(helper->cmd, &helper->env, exit_s);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
	}
	else
		execute_forked_cmd(helper, exit_s, &status);
	if (WIFEXITED(status))
		*exit_s = WEXITSTATUS(status);
	if (helper->inf > 0)
		close(helper->inf);
	if (helper->outf > 0)
		close(helper->outf);
	if (cmd->file->here_doc > 0)
		close(cmd->file->here_doc);
}

void closes_helper(int inf, int outf, t_cmd *full, int *pipefd, int perv_pipe)
{
	if (inf  > 0)
		close(inf);
	if (outf > 0)
		close(outf);
	if (full->file->here_doc > 0)
		close(full->file->here_doc);
	handelprevpipe(pipefd, &perv_pipe);
}


void take_child(t_cmd *full, char **path, int *exit_s, t_env **env)
{
	char	*pathh;
	char	**cmd = full->args;

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
		{
			fprintf(stderr, "minishell:%s : command not found\n", cmd[0]);
			ft_malloc(0, 0);
			exit(127);
		} 
		if (!(*env)->env_v)
			execve(pathh, cmd, NULL);
		if (cmd[0][0] == '\0')
		{
			fprintf(stderr, "minishell:%s : command not found\n", cmd[0]);
			ft_malloc(0, 0);
			exit(127);
		}
		else
		{
			execve(pathh, cmd, (*env)->env_v);
			perror("execve failed");
		}
		ft_malloc(0, 0);
		exit(126);
	}
}

void save_exit_s(int count, int *exit_s)
{
	int	status;
	int exit_status;

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


void exectution(t_cmd *full, t_env **env, int *exit_s)
{
	int 	inf = 0;
	int		outf = 0;
	char	**path = NULL;
	pid_t	pid;
	int		pipefd[2];
	int	perv_pipe = -1;
	int count  = 0;

	path = takepaths(env);
	if (full->next )
	{
		while(full)
		{
			pipecheck(pipefd);
			pid = fork();
			here_doc_helper = 1337;
			if (forkfaild(pid, pipefd))
			{
				ft_malloc(0,0);
				exit(128);
			}
			if (pid == 0)
			{
				exectution_helper(inf,outf,pipefd,full, perv_pipe);
				if (full->args && inf != -5 && outf != -5)// 
					take_child(full, path, exit_s,env);
				else if (!full->args)
				{
					close_helper(inf, outf, full, pipefd, perv_pipe);
					return ;
				}
			}
			else
			{
				close_helper(inf, outf,full,pipefd,perv_pipe);
				if (full->file->here_doc > 0)
					close(full->file->here_doc);
				handelprevpipe(pipefd, &perv_pipe);
				count++;
			}
			full = full->next;
		}
		close(pipefd[0]);
		save_exit_s(count,exit_s);
	}
	else
		execute_single_cmd(full, env, exit_s);
}
