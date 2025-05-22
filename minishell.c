/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:45:06 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/22 11:12:08 by rlamlaik         ###   ########.fr       */
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
void print_files(t_file *file)
{
	int i = 0;
	while (file)
	{
		printf("  File %d:\n", i++);
		printf("    infile: %s\n", file->infile ? file->infile : "NULL");
		printf("    outfile: %s\n", file->outfile ? file->outfile : "NULL");
		printf("    append: %d\n", file->append);
		printf("    here_doc: %d\n", file->here_doc);
		printf("    flag: %d\n", file->flag);
		file = file->next;
	}
}

void print_cmds(t_cmd *cmd)
{
	int i = 0;
	while (cmd)
	{
		printf("Command %d:\n", i++);
		if (cmd->args)
		{
			printf("  args: ");
			for (int j = 0; cmd->args[j]; j++)
				printf("\"%s\" ", cmd->args[j]);
			printf("\n");
		}
		else
		{
			printf("  args: NULL\n");
		}
		if (cmd->file)
			print_files(cmd->file);
		else
			printf("  No associated files.\n");

		cmd = cmd->next;
	}
}
void	print_token_list(t_token *head)
{
	while (head)
	{
		printf("Type: %d\n", head->type);
		printf("Value: %s\n", head->value ? head->value : "(null)");
		printf("Ambiguous: %s\n", head->ambiguous ? head->ambiguous : "(null)");
		printf("Quoted: %d\n", head->quoted);
		printf("Flag_mbg: %d\n", head->flag_mbg);
		printf("-----\n");
		head = head->next;
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
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))// 
		return(1);
	(void)av;
	(void)ac;
	int g = 0;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	env_list = linked_varibles(env);
	env_list->emg_flag = 0;

	while(1)
	{
		g = 0;
		here_doc_helper = 1;
		line = readline("realSHELL $> ");
		here_doc_helper = 0;
		if (!line)
		{
			char *args[] = {"exit", NULL};
			// ft_malloc(0, 0);
			ft_exit(args , exit_s);
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

