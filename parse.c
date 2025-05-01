#include "minishell.h"

int is_redirection(t_token *tokens)
{
	return (tokens->type == TOKEN_HEREDOC || tokens->type == TOKEN_APPEND ||
		tokens->type == TOKEN_REDIR_OUT || tokens->type == TOKEN_REDIR_IN ||
		tokens->type == TOKEN_PIPE);
}

void	syntax(t_token *tokens, int *exit_s)
{
	if (!tokens || is_redirection(tokens) || tokens->type == TOKEN_PIPE)
	{
		*exit_s = 2;
		printf("syntax error\n");
		return ;
	}

	while (tokens)
	{
		if (is_redirection(tokens))
		{
			if (!tokens->next || tokens->next->type == TOKEN_EOF ||
				tokens->next->type == TOKEN_PIPE ||is_redirection(tokens->next))
			{
				*exit_s = 2;
				printf("syntax errorn\n");
				return ;
			}
		}

		if (tokens->type == TOKEN_PIPE)
		{
			if (!tokens->next || tokens->next->type == TOKEN_EOF)
			{
				*exit_s = 2;
				printf("syntax error\n");
				return ;
			}
		}
		tokens = tokens->next;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	char			*s;
	size_t			p;

	i = 0;
	p = size * count;
	if (size && p / size != count)
		return (0);
	s = (char *)ft_malloc(size * count, 1);
	if (!s)
		return (NULL);
	while (i < (size * count))
	{
		s[i] = 0;
		i++;
	}
	return (s);
}

void add_arg(t_cmd *type, char *value)
{
	int count = 0;
	int i;
	int j;
	char **new_args;

	count = 0;
	if (type->args)
	{
		while (type->args[count])
			count++;
	}
	new_args = ft_malloc(sizeof(char *) * (count + 2), 1);
	if (!new_args)
		return;
	i = 0;
	while (i < count)
	{
		new_args[i] = ft_strdup(type->args[i]);
		i++;
	}
	new_args[count] = ft_strdup(value);
	new_args[count + 1] = NULL;
	if (type->args)
	{
		j = 0;
		while (type->args[j])
			free(type->args[j++]);
		free(type->args);
	}
	type->args = new_args;
}

void	token_infile(t_token *tokens, t_file *file)
{
	t_file	*last_file;
	t_file	*new_file;

	last_file = NULL;
	new_file = ft_calloc(1, sizeof(t_file));
	if (!new_file)
		return ;
	if (!last_file)
	{
		file->infile = tokens->next->value;
		last_file = file;
	}
	else
	{
		last_file->next = new_file;
		last_file = new_file;
		new_file->infile = tokens->next->value;
	}
	tokens = tokens->next;
}

void	token_outfile(t_file *file, t_token *tokens)
{
	t_file	*last_file;
	t_file	*new_file;

	last_file = NULL;
	new_file = ft_calloc(1, sizeof(t_file));
	if (!new_file)
		return ;
	if (!last_file)
	{
		file->outfile = tokens->next->value;
		file->append = 0;
		last_file = file;
	}
	else
	{
		last_file->next = new_file;
		last_file = new_file;
		new_file->outfile = tokens->next->value;
		new_file->append = 0;
	}
	tokens = tokens->next;
}

void	token_append(t_file *file, t_token *tokens)
{
	t_file	*new_file;
	t_file	*last_file;

	last_file = NULL;
	new_file = ft_calloc(1, sizeof(t_file));
	if (!last_file)
	{
		file->outfile = tokens->next->value;
		file->append = 1;
		last_file = file;
	}
	else
	{
		last_file->next = new_file;
		last_file = new_file;
		new_file->outfile = tokens->next->value;
		new_file->append = 1;
	}
	tokens = tokens->next;
}

void	token_heredoc(t_file *file, t_token *tokens)
{
	t_file *last_file;
	t_file *new_file;

	last_file = NULL;
	new_file = ft_calloc(1, sizeof(t_file));
	if(!last_file)
	{
		file->here_doc = heredoc(tokens->next->value);
		printf("helooooo %d\n", file->here_doc);
		last_file = file;
	}
	else
	{
		last_file->next = new_file;
		last_file = new_file;
		new_file->here_doc = heredoc(tokens->next->value);
		printf("helooooo %d\n", file->here_doc);
	}
	tokens = tokens->next;
}

// t_cmd *parse_tokens(t_token *tokens)
// {
// 	t_cmd	*cmd;
// 	t_file	*file;
// 	t_file	*last_file;
// 	t_cmd	*start;
// 	t_file	*new_file;
// 	t_cmd	*new_cmd;

// 	file = ft_calloc(1, sizeof(t_file));
// 	cmd = ft_calloc(1, sizeof(t_cmd));
// 	new_file = ft_calloc(1, sizeof(t_file));
// 	if (!file | !cmd)
// 		return (NULL);
// 	last_file = NULL;
// 	start = cmd;
// 	cmd->file = file;
// 	while (tokens)
// 	{
// 		while (tokens && tokens->type != TOKEN_PIPE)
// 		{
// 			if (tokens->type == TOKEN_WORD)
// 				add_arg(cmd, tokens->value);
// 			else if (tokens->type == TOKEN_REDIR_IN && tokens->next)
// 			{
// 				// token_infile(tokens, file);
// 				if (!last_file)
// 				{
// 					file->infile = tokens->next->value;
// 					last_file = file;
// 				}
// 				else
// 				{
// 					last_file->next = new_file;
// 					last_file = new_file;
// 					new_file->infile = tokens->next->value;
// 				}
// 				tokens = tokens->next;
// 			}
// 			else if (tokens->type == TOKEN_REDIR_OUT && tokens->next)
// 			{
// 				// token_outfile(file, tokens);
// 				if (!last_file)
// 				{
// 					file->outfile = tokens->next->value;
// 					file->append = 0;
// 					last_file = file;
// 				}
// 				else
// 				{
// 					last_file->next = new_file;
// 					last_file = new_file;
// 					new_file->outfile = tokens->next->value;
// 					new_file->append = 0;
// 				}
// 				tokens = tokens->next;
// 			}
// 			else if (tokens->type == TOKEN_APPEND && tokens->next)
// 			{
// 				// token_append(file, tokens);
// 				if (!last_file)
// 				{
// 					file->outfile = tokens->next->value;
// 					file->append = 1;
// 					last_file = file;
// 				}
// 				else
// 				{
// 					last_file->next = new_file;
// 					last_file = new_file;
// 					new_file->outfile = tokens->next->value;
// 					new_file->append = 1;
// 				}
// 				tokens = tokens->next;
// 			}
// 			else if (tokens->type == TOKEN_HEREDOC && tokens->next)
// 			{
// 				// token_heredoc(file, tokens);
// 				if(!last_file)
// 				{
// 					file->here_doc = heredoc(tokens->next->value);
// 					printf("helooooo %d\n", file->here_doc);
// 					last_file = file;
// 				}
// 				else
// 				{
// 					last_file->next = new_file;
// 					last_file = new_file;
// 					new_file->here_doc = heredoc(tokens->next->value);
// 					printf("helooooo %d\n", file->here_doc);
// 				}
// 				tokens = tokens->next;
// 			}
// 		}
// 		if (tokens && tokens->type == TOKEN_PIPE)
// 		{
// 			new_cmd = ft_calloc(1, sizeof(t_cmd));
// 			new_cmd->file = new_file;
// 			cmd->next = new_cmd;
// 			cmd = new_cmd;
// 			tokens = tokens->next;
// 			file = new_file;
// 			last_file = NULL;
// 		}
// 	}
// 	// print_cmds(start);
// 	return (start);
// }

t_cmd *parse_tokens(t_token *tokens)
{
	t_cmd *cmd;
	t_file *file;
	t_file *last_file = NULL;

	file = ft_calloc(1, sizeof(t_file));
	if (!file)
		return (NULL);
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	t_cmd *start = cmd;
	cmd->file = file;

	while (tokens)
	{
		while (tokens && tokens->type != TOKEN_PIPE)
		{
			if (tokens->type == TOKEN_WORD)
				add_arg(cmd, tokens->value);
			else if (tokens->type == TOKEN_REDIR_IN && tokens->next)
			{
				if (!last_file)
				{
					file->infile = tokens->next->value;
					last_file = file;
				}
				else
				{
					t_file *new_file = ft_calloc(1, sizeof(t_file));
					last_file->next = new_file;
					last_file = new_file;
					new_file->infile = tokens->next->value;
				}
				tokens = tokens->next;
			}
			else if (tokens->type == TOKEN_REDIR_OUT && tokens->next)
			{
				if (!last_file)
				{
					file->outfile = tokens->next->value;
					file->append = 0;
					last_file = file;
				}
				else
				{
					t_file *new_file = ft_calloc(1, sizeof(t_file));
					last_file->next = new_file;
					last_file = new_file;
					new_file->outfile = tokens->next->value;
					new_file->append = 0;
				}
				tokens = tokens->next;
			}
			else if (tokens->type == TOKEN_APPEND && tokens->next)
			{
				if (!last_file)
				{
					file->outfile = tokens->next->value;
					file->append = 1;
					last_file = file;
				}
				else
				{
					t_file *new_file = ft_calloc(1, sizeof(t_file));
                    last_file->next = new_file;
                    last_file = new_file;
                    new_file->outfile = tokens->next->value;
                    new_file->append = 1;
				}
				tokens = tokens->next;
			}
			else if (tokens->type == TOKEN_HEREDOC && tokens->next)
			{
				// token_heredoc(file, tokens);
				if(!last_file)
				{
					file->here_doc = heredoc(tokens->next->value);
					printf("helooooo %d\n", file->here_doc);
					last_file = file;
				}
				else
				{
					t_file *new_file = ft_calloc(1, sizeof(t_file));
					last_file->next = new_file;
					last_file = new_file;
					new_file->here_doc = heredoc(tokens->next->value);
					printf("helooooo %d\n", file->here_doc);
				}
				tokens = tokens->next;
			}
			tokens = tokens->next;
		}

		if (tokens && tokens->type == TOKEN_PIPE)
		{
			t_cmd *new_cmd = ft_calloc(1, sizeof(t_cmd));
			t_file *new_file = ft_calloc(1, sizeof(t_file));

			new_cmd->file = new_file;
			cmd->next = new_cmd;
			cmd = new_cmd;
			tokens = tokens->next;
			file = new_file;
			last_file = NULL;
		}
	}
	return (start);
}