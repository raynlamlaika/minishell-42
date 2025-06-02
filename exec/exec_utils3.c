/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:00:54 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/02 08:19:15 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handelprevpipe(int *pipefd, int *prev_pipe)
{
	if (pipefd[1] > 0)
		close(pipefd[1]);
	if (*prev_pipe > 0)
		close(*prev_pipe);
	*prev_pipe = pipefd[0];
}

int	is_passed(char *str, char *sec)
{
	int	i;

	i = 0;
	while (str[i] || sec[i])
	{
		if (str[i] != sec[i])
			return (0);
		i++;
	}
	return (1);
}

int	search_search(char *str)
{
	if (is_passed(str, "echo") || is_passed(str, "cd") || \
		is_passed(str, "pwd") || is_passed(str, "export") || \
		is_passed(str, "unset") || is_passed(str, "env") || \
		is_passed(str, "exit"))
		return (1);
	else
		return (0);
}

void	buildin(t_cmd *cmd, t_env **env, int *exit_s)
{
	if (is_passed(cmd->args[0], "echo"))
		ft_echo(cmd->args, *exit_s);
	if (is_passed(cmd->args[0], "exit"))
		ft_exit(cmd->args, *exit_s);
	else if (is_passed(cmd->args[0], "export"))
		ft_export(cmd->args, env);
	else if (is_passed(cmd->args[0], "cd"))
		ft_cd(cmd->args, *env);
	else if (is_passed(cmd->args[0], "pwd"))
		ft_pwd(*env);
	else if (is_passed(cmd->args[0], "env"))
	{
		if (!cmd->args[1])
			ft_env(*env);
		else
			printf_error("minishell: env: env with no options\n");
	}
	else if (is_passed(cmd->args[0], "unset"))
		ft_unset(cmd->args, env);
}
