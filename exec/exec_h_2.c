/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_h_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:16:45 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/19 11:44:12 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	helper_s(t_finished *helper)
{
	struct stat	sb;

	if (ft_strchr(helper->args[0], '/'))
	{
		if (stat(helper->args[0], &sb) == 0)
		{
			if (S_ISDIR(sb.st_mode))
			{
				print_error_arg("minishell: ", helper->args[0], \
					": Is a directory\n");
				ft_malloc(0, 0);
				exit(126);
			}
		}
		else
			print_error_arg("", helper->args[0], \
				" : command not found\n");
	}
	else
		print_error_arg("minishell ", helper->args[0], \
			":No  \n");
	ft_malloc(0, 0);
	exit(127);
}

void	null_arg(void)
{
	printf_error("minishell: : command not found\n");
	ft_malloc(0, 0);
	exit(127);
}

void	execute_command_s(t_finished *helper, int *exit_s)
{
	char	**path;

	path = takepaths(&helper->env);
	helper->bin = pick(path, helper->args[0]);
	if (!helper->bin && helper->args[0][0] != '\0')
	{
		execve(helper->args[0], helper->args, helper->env->env_v);
		if (ft_strrchr(helper->args[0], '$') == NULL)
			print_error_arg("", helper->args[0], " : command not found\n");
		*exit_s = 127;
		ft_malloc(0, 0);
		exit(*exit_s);
	}
	if (helper->args[0][0] == '\0')
		null_arg();
	if (!helper->env->env_v)
		execve(helper->bin, helper->args, NULL);
	execve(helper->bin, helper->args, helper->env->env_v);
	if (ft_strchr(helper->args[0], '/'))
		helper_s(helper);
	print_error_arg("", helper->args[0], " : command not found\n");
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
