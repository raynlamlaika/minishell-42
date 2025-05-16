/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:45:49 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/15 21:01:02 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_single_cmd(t_cmd *cmd, t_env *env, char **path, int *exit_s)
{
	int		inf;
	int		outf;
	char	**args;
	int		status;

	args = cmd->args;

	get_redirections(&inf, &outf, cmd);
	if (!cmd->args || !cmd->args[0])
		;
	else if (search_search(cmd->args[0]))
		buildin(cmd, &env, exit_s);
	else if (!search_search(cmd->args[0]))
	{
		pid_t pid = fork();
		if (pid == -1)
			printf("minishell: `fork' failed to creat a Child\n");
		if (pid == 0)
		{
			if (inf != -1)
			{
				dup2(inf, STDIN_FILENO);
				close(inf);
			}
			if (outf != -1)
			{
				dup2(outf, STDOUT_FILENO);
				close(outf);
			}
			char *bin = pick(path, args[0]);
			if (!bin)
			{
				execve(args[0], args, env->env_v);
				printf("%s: command not found\n", args[0]);
				exit(127);
			}
			if (args[0][0] == '\0')
			{
				printf("minishell: : command not found\n");
				exit(127);
			}
			execve(bin, args, env->env_v);
			printf("%s: command not found\n", args[0]);
			exit(126);
		}
		else
			waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			*exit_s = WEXITSTATUS(status);
	}
}

void exectution(t_cmd *full, t_env *env, int *exit_s)
{
	int 	inf, outf;
	char    **path = NULL;
	pid_t	pid;
	int		pipefd[2];
	char**	cmd;
	int	perv_pipe = -1;
	int status;
	int count  = 0;
	path = takepaths(&env);
	if (full->next )
	{
		while(full)
		{
			pipecheck(pipefd);
			pid = fork();
			if (forkfaild(pid, pipefd))
				break;
			if (pid == 0)
			{
				get_redirections(&inf, &outf, full);
				if (inf != -1)
				{
					dup2(inf, STDIN_FILENO);
					close(inf);
				}
				else if (perv_pipe != -1)
					dup2(perv_pipe, STDIN_FILENO);

				if (outf != -1)
				{
					dup2(outf, STDOUT_FILENO);
					close(outf);
				}
				else if (full->next)
					dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[0]);
				close(pipefd[1]);
				if (full->args)
				{
					if (search_search(full->args[0]) == 1)
					{
						buildin(full,&env, exit_s);
						exit(*exit_s);
					}
					else
					{
						cmd = full->args;
						char *pathh = pick(path, cmd[0]);
						if (!pathh)
						{
							perror("command not found");
							exit(127);
						}
						execve(pathh, cmd, env->env_v);
						perror("execve failed");
						exit(126);
					}
				}
				else if (!full->args)
					return ;
			}
			else
			{
				handelprevpipe(pipefd, &perv_pipe);
				count++;
			}
			full = full->next;
		}
		while (count > 0)
		{
			wait(&status);
			count--;
			if (WIFEXITED(status))
			{
				int exit_status = WEXITSTATUS(status);
				*exit_s = exit_status;
			}
		}
	}
	else
		execute_single_cmd(full, env, path, exit_s);
}
