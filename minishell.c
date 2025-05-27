/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:45:06 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/27 03:31:23 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int here_doc_helper = 0;

/*


void print_token(t_token *token) {
    while (token) 
	{
		fprintf(stderr, "Ambiguous: %s\n", token->ambiguous);
        token = token->next;
    }
}


void print_files(t_file *file)
{
	int i = 0;
	while (file)
	{
		fprintf(stderr, "  File %d:\n", i++);
		fprintf(stderr, "    infile: %s\n", file->infile ? file->infile : "NULL");
		fprintf(stderr, "    outfile: %s\n", file->outfile ? file->outfile : "NULL");
		fprintf(stderr, "    append: %d\n", file->append);
		fprintf(stderr, "    here_doc: %d\n", file->here_doc);
		fprintf(stderr, "    flag: %d\n", file->flag);
		file = file->next;
	}
}

void print_cmds(t_cmd *cmd)
{
	int i = 0;
	while (cmd)
	{
		fprintf(stderr, "Command %d:\n", i++);
		if (cmd->args)
		{
			fprintf(stderr, "  args: ");
			for (int j = 0; cmd->args[j]; j++)
				fprintf(stderr, "\"%s\" ", cmd->args[j]);
			fprintf(stderr, "\n");
		}
		else
		{
			fprintf(stderr, "  args: NULL\n");
		}
		if (cmd->file)
			print_files(cmd->file);
		else
			fprintf(stderr, "  No associated files.\n");

		cmd = cmd->next;
	}
}
void	print_token_list(t_token *head)
{
	while (head)
	{
		fprintf(stderr, "Type: %d\n", head->type);
		fprintf(stderr, "Value: %s\n", head->value);
		fprintf(stderr, "Ambiguous: %s\n", head->ambiguous ? head->ambiguous : "(null)");
		fprintf(stderr, "Quoted: %d\n", head->quoted);
		fprintf(stderr, "Flag_mbg: %d\n", head->flag_mbg);
		fprintf(stderr, "-----\n");
		head = head->next;
	}
}

*/
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
int *ff()
{
	static int i;
	return(&i);
}

int main(int ac,char **av,char**env)
{
	int *exit_s = ff();
	static int here_doc;
	char *args[] = {"exit", NULL};
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
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
			return(1);
	while(1)
	{
		if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
			return(1);
		g = 0;
		here_doc_helper = 1;
		line = readline("realSHELL $> ");
		here_doc_helper = 0;
		if (!line)
		{
			ft_exit(args , *exit_s);
			rl_clear_history();
			return (*exit_s);
		}
		add_history(line);
		tokens = lexer(line, last, 0);
		if (tokens)
			g = syntax(tokens, exit_s, here_doc);
		if (g == 0)
		{
			expand(tokens, env_list, exit_s);
			int i = syntax_ambiguous(tokens, exit_s);
			if (i == 0)
			{
				t_cmd *f =  parse_tokens(tokens,env_list);
				if (here_doc_helper == 20)
				{
					dup2(2, 0);
					continue;
				}
				exectution(f, &env_list, exit_s);
			}
		}
		here_doc_helper = 0;
		free(line);
	}
	return (*exit_s);
}
