/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_pipe_h.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:32:04 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/02 08:20:21 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipecheck(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		printf_error("minishell :`Pipe` can't open\n");
		return (0);
	}
	return (1);
}

int	forkfaild(pid_t pid, int*pipefd)
{
	int	i;

	i = 0;
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		i++;
	}
	return (i);
}
