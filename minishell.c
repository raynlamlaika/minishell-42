/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:45:06 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/01 23:28:08 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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

	if (!line)
	{
		args = ft_split("exit", ' ');
		ft_exit(args, *exit_s);
		free(line);
		rl_clear_history();
	}
}

int	passed(t_token *tokens, t_env*env_list, int*exit_s)
{
	t_cmd	*f;

	disconnect_flagged_nodes(&tokens);
	f = parse_tokens(tokens, env_list);
	if (g_here_doc_helper == 20)
	{
		dup2(2, 0);
		return (0);
	}
	exectution(f, &env_list, exit_s);
	return (1);
}

void	print_token(t_token *token)
{
	while (token)
	{
		fprintf(stderr, "Ambiguous: %s\n", token->value);
		token = token->next;
	}
}

int	helper_looop(t_token *tks, int*exit_s, int here_doc)
{
	int	g;

	g = 0 ;
	if (tks)
		g = syntax(tks, exit_s, here_doc);
	return (g);
}

int	helper_loop(char*line, t_token*tks, int*exit_s, t_env*env)
{
	int			here_doc;
	t_token		*last;
	int			g;

	(1) && (last = NULL, here_doc = 0);
	while (1)
	{
		if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
			return (1);
		(1) && (g = 0, g_here_doc_helper = 1, line = readline("realSHELL $> "));
		g_here_doc_helper = 133;
		check_line_null(exit_s, line);
		if (*line)
			add_history(line);
		tks = lexer(line, last, 0);
		g = helper_looop(tks, exit_s, here_doc);
		if (g == 0)
		{
			(1) && (g = expand(tks, env, exit_s), g = synx_ambg(tks, exit_s));
			if (g == 0)
				if (!passed(tks, env, exit_s))
					continue ;
		}
		free(line);
	}
}

int	main(int ac, char**av, char**env)
{
	int		*exit_s;
	char	*line;
	t_token	*tokens;
	t_env	*env_list;

	(void)av;
	(void)ac;
	exit_s = exit_status(0, 0);
	line = NULL;
	tokens = NULL;
	env_list = linked_varibles(env);
	env_list->emg_flag = 0;
	get_current_dir(env_list);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (1);
	return (helper_loop(line, tokens, exit_s, env_list), *exit_s);
}
