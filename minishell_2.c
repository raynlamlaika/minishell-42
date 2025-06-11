/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 03:30:00 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/11 00:33:06 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_here_doc_helper = 0;

int	*exit_status(int more, int value)
{
	static int	status;

	if (more == 1)
		status = value;
	return (&status);
}

void	disconnect_flagged_nodes(t_token **head)
{
	t_token	*current;
	t_token	*prev;
	t_token	*next_node;

	prev = NULL;
	current = *head;
	while (current)
	{
		next_node = current->next;
		if (current->rm_node == 10)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			current->next = NULL;
		}
		else
			prev = current;
		current = next_node;
	}
}

void	check_line_null(int*exit_s, char*line)
{
	char	**args;
	t_cmd	*cmd;

	cmd = ft_malloc(sizeof(t_cmd), 1);
	cmd->exit_flag = 42;
	if (!line)
	{
		args = ft_split("exit", ' ');
		ft_exit(args, *exit_s, cmd);
		ft_malloc(0, 0);
		free(line);
		rl_clear_history();
	}
}
