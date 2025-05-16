/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:42:51 by abouabba          #+#    #+#             */
/*   Updated: 2025/05/15 20:00:52 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	handle_signal(int sig)
{
	if (here_doc_helper == 1 && sig == SIGINT)
	{
		if (here_doc_helper != 20)
			write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (here_doc_helper == 42 && sig == SIGINT)
	{
		here_doc_helper = 20;
		close(0);
	}
}
