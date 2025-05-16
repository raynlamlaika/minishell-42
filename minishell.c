/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:45:06 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/16 01:24:51 by rlamlaik         ###   ########.fr       */
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
	int i = 1;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	env_list = linked_varibles(env);
	char *ll = expnd_cd("PATH", env_list);
	if (!ll)
	{
		t_env *tt = new_node("PATH",PATH);
		append_node(&env_list, tt);
	}
	if (isatty(STDIN_FILENO))
	{
		while(i)
		{
			g = 0;
			here_doc_helper = 1;
			line = readline("realSHELL $> ");
			here_doc_helper = 0;
			if (!line) 
			{
				ft_malloc(0, 0);
				free_env_list(env_list);
				free(line);
				return (1);
			}
			add_history(line);
			tokens = lexer(line, last, 0);
			if (tokens)
				g = syntax(tokens, &exit_s, here_doc);
			if (g == 0)
			{
				expand(tokens, env_list);
				// here the emg 
				t_cmd *f =  parse_tokens(tokens,env_list);
				if (here_doc_helper == 20)
				{
					dup2(2, 0);
					continue;
				}
				exectution(f, env_list, &exit_s);
			}
			ft_malloc(0, 0);
			free(line);
			i++;
		}
		free(line);
		ft_malloc(0, 0);
		free_env_list(env_list);
		return (exit_s);
	}
}

