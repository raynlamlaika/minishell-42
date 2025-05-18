/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:45:06 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/18 19:07:56 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


int here_doc_helper = 0;



void print_token(t_token *token) {
    while (token) 
	{
		printf("Ambiguous: %s\n", token->ambiguous);
        token = token->next;
    }
}

int get_list_size(t_env *head) {
    int size = 0;
    t_env *current = head;

    // Traverse through the list and count the nodes
    while (current != NULL) {
        size++;
        current = current->next;
    }

    return size;
}

int main(int ac,char **av,char**env)
{
	static int exit_s;
	static int here_doc;
	char *line;
	t_token *tokens;
	t_token* last = NULL;
	t_env	*env_list;

	(void)av;
	(void)ac;
	int g = 0;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	env_list = linked_varibles(env);
	env_list->emg_flag = 0;
	if (isatty(STDIN_FILENO) || isatty(STDOUT_FILENO))
	{
		while(1)
		{
			g = 0;
			here_doc_helper = 1;
			line = readline("realSHELL $> ");
			here_doc_helper = 0;
			if (!line)
			{
				ft_malloc(0, 0);
				// free_env_list(env_list);
				rl_clear_history();
				return (exit_s);
			}
			add_history(line);
			tokens = lexer(line, last, 0);
			if (tokens)
				g = syntax(tokens, &exit_s, here_doc);
			if (g == 0)
			{
				expand(tokens, env_list, &exit_s);
				int i = syntax_ambiguous(tokens, &exit_s);
				if (i == 0)
				{
					t_cmd *f =  parse_tokens(tokens,env_list);
					if (here_doc_helper == 20)
					{
						dup2(2, 0);
						continue;
					}
					exectution(f, &env_list, &exit_s);
				}
			}
			free(line);
		}
		return (exit_s);
	}
}

