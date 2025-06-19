/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:21:15 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/19 11:48:32 by abouabba         ###   ########.fr       */
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

void	buitin(t_finished *helper, int *exit_s)
{
	int	saved_stdin;
	int	saved_stdout;

	if (ft_strcmp(helper->cmd->args[0], "exit"))
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
	}
	if (helper->inf != -1)
		(1) && (dup2(helper->inf, STDIN_FILENO), close(helper->inf));
	if (helper->outf != -1)
		(1) && (dup2(helper->outf, STDOUT_FILENO), close(helper->outf));
	buildin(helper->cmd, &helper->env, exit_s);
	if (ft_strcmp(helper->cmd->args[0], "exit"))
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
	}
}

void	close_inf_out(t_finished *helper, t_cmd *cmd)
{
	if (helper->inf > 0)
		close(helper->inf);
	if (helper->outf > 0)
		close(helper->outf);
	if (cmd->file->here_doc > 0)
		close(cmd->file->here_doc);
	return ;
}

void	execute_single_cmd(t_cmd *cmd, t_env **env, int *exit_s)
{
	t_finished	*helper;
	int			status;

	status = 0;
	cmd->exit_flag = 42;
	helper = ft_malloc(sizeof(t_finished), 1);
	initialize_helper(helper, cmd, env);
	if (!helper->args || !helper->args[0] \
	|| helper->inf == -5 || helper->outf == -5)
	{
		close_inf_out(helper, cmd);
		exit_status(1, 1);
		return ;
	}
	if (search_search(helper->args[0]) == 1)
		buitin(helper, exit_s);
	else
	{
		execute_forked_cmd(helper, exit_s, &status);
		if (WIFEXITED(status))
			*exit_s = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			*exit_s = 128 + WTERMSIG(status);
	}
	close_inf_out(helper, cmd);
}
