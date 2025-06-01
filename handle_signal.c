/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:42:51 by abouabba          #+#    #+#             */
/*   Updated: 2025/06/01 17:04:53 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	if (g_here_doc_helper == 1 && sig == SIGINT)
	{
		if (g_here_doc_helper != 42)
			write(2, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit_status(1, 130);
	}
	if (g_here_doc_helper == 42 && sig == SIGINT)
	{
		g_here_doc_helper = 20;
		close(0);
		exit_status(1, 130);
	}
	if (g_here_doc_helper == 133 && sig == SIGINT)
	{
		write (2, "\n", 1);
	}
}
