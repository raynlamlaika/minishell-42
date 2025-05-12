#include "minishell.h"

int is_redirection(t_token *tokens)
{
	return (tokens->type == TOKEN_HEREDOC || tokens->type == TOKEN_APPEND ||
		tokens->type == TOKEN_REDIR_OUT || tokens->type == TOKEN_REDIR_IN ||
		tokens->type == TOKEN_PIPE);
}

void	syntax_2(t_token **tokens, int *exit_s)
{
	if (is_redirection(*tokens))
	{
		if (!(*tokens)->next || (*tokens)->next->type == TOKEN_EOF
			|| (*tokens)->next->type == TOKEN_PIPE
			|| is_redirection((*tokens)->next))
		{
			*exit_s = 2;
			printf("minishell: syntax error near unexpected token `newline'\n");
			return ;
		}
	}
	if ((*tokens)->type == TOKEN_PIPE)
	{
		if (!(*tokens)->next || (*tokens)->next->type == TOKEN_EOF)
		{
			*exit_s = 2;
			printf("minishell: syntax error near unexpected token `newline'\n");
			return ;
		}
	}
}

int	syntax(t_token *tokens, int *exit_s, int max_here_doc)
{
	if (!tokens || !tokens->value)
	{
		*exit_s = 2;
		return (1);
	}
	if (tokens->type == TOKEN_PIPE)
	{ 
		*exit_s = 2;
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	while (tokens)
	{
		if (tokens->type ==  TOKEN_HEREDOC)
		{
			max_here_doc++;
			if (max_here_doc > 16)
			{
				printf("bash: maximum here-document count exceeded\n");
				exit(2);
			}
		}
		syntax_2(&tokens, exit_s);
		if (*exit_s == 2)
			return (0);
		tokens = tokens->next;
	}
	return (0);
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

void print_cmds(t_cmd *cmd)
{
	int i;
	int num = 1;
	t_file *hh = cmd ->file;
	while (cmd)
	{
		printf("\n--- Command %d ---\n", num++);
        while (hh)
        {
            printf("this is %s \n", hh->infile);
            hh = hh->next;  
        }
		if (cmd->file)
		{
			printf("infile: %s\n", cmd->file->infile);
			printf("outfile: %s\n", cmd->file->outfile);
		}
		printf("append: %d\n", cmd->file->append);
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			printf("arg[%d]: %s\n", i, cmd->args[i]);
			i++;
		}
		cmd = cmd->next;
	}
}

void add_arg(t_cmd *type, char *value)
{
	int		count;
	int		i;
	int		j;
	char	**new_args;

	count = 0;
	if (type->args)
	{
		while (type->args[count])
			count++;
	}
	new_args = ft_malloc(sizeof(char *) * (count + 2), 1);
	if (!new_args)
		return ;
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
		// while (type->args[j])
		// 	free(type->args[j++]);
		// free(type->args);
	}
	type->args = new_args;
}

void	token_infile(t_file **last_file, t_file *file, t_token *tokens)
{
	t_file *new_file;

	if (!*last_file)
	{
		file->infile = tokens->next->value;
		*last_file = file;
	}
	else
	{
		new_file = ft_calloc(1, sizeof(t_file));
		(*last_file)->next = new_file;
		*last_file = new_file;
		new_file->infile = tokens->next->value;
	}
}

void	token_outfile(t_file **last_file, t_file *file, t_token *tokens)
{
	t_file *new_file;

	if (!*last_file)
	{
		file->outfile = tokens->next->value;
		file->append = 0;
		*last_file = file;
	}
	else
	{
		new_file = ft_calloc(1, sizeof(t_file));
		(*last_file)->next = new_file;
		*last_file = new_file;
		new_file->outfile = tokens->next->value;
		new_file->append = 0;
	}
}

void	token_append(t_file **last_file, t_file *file, t_token *tokens)
{
	t_file *new_file;
	if (!*last_file)
	{
		file->outfile = tokens->next->value;
		file->append = 1;
		*last_file = file;
	}
	else
	{
		new_file = ft_calloc(1, sizeof(t_file));
		(*last_file)->next = new_file;
		*last_file = new_file;
		new_file->outfile = tokens->next->value;
		new_file->append = 1;
	}
}

void	token_heredoc(t_file **last_file, t_file *file, t_token *tokens ,t_env *env)
{
	t_file *new_file;

	if(!*last_file)
	{
		file->here_doc = heredoc(tokens->next->value, env);
		*last_file = file;
	}
	else
	{
		new_file = ft_calloc(1, sizeof(t_file));
		(*last_file)->next = new_file;
		*last_file = new_file;
		new_file->here_doc = heredoc(tokens->next->value, env);
	}
}

t_token	*parse_tokens_helper(t_cmd *cmd, t_token *tokens, t_file **last_file, t_file *file, t_env *env)
{
	if (tokens->type == TOKEN_WORD)
		add_arg(cmd, tokens->value);
	else if (tokens->type == TOKEN_REDIR_IN && tokens->next)
	{
		token_infile(last_file, file, tokens);
		tokens = tokens->next;
	}
	else if (tokens->type == TOKEN_REDIR_OUT && tokens->next)
	{
		token_outfile(last_file, file, tokens);
		tokens = tokens->next;
	}
	else if (tokens->type == TOKEN_APPEND && tokens->next)
	{
		token_append(last_file, file, tokens);
		tokens = tokens->next;
	}
	else if (tokens->type == TOKEN_HEREDOC && tokens->next)
	{
		token_heredoc(last_file, file, tokens, env);
		tokens = tokens->next;
	}
	return (tokens->next);
}

void	parse_tokens_utils(t_file **file, t_token **tokens, t_file **last_file, t_cmd **cmd)
{
	t_cmd	*new_cmd;
	t_file	*new_file;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	new_file = ft_calloc(1, sizeof(t_file));
	if (!new_cmd || !new_file)
		return;
	new_cmd->file = new_file;
	(*cmd)->next = new_cmd;
	*cmd = new_cmd;
	*tokens = (*tokens)->next;
	*file = new_file;
	*last_file = NULL;
}

t_cmd *parse_tokens(t_token *tokens, t_env *env)
{
	t_cmd *cmd;
	t_file *file;
	t_file *last_file;

	file = ft_calloc(1, sizeof(t_file));
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd || !file)
		return (NULL);
	t_cmd *start = cmd;
	cmd->file = file;
	last_file = NULL;
	while (tokens)
	{
		while (tokens && tokens->type != TOKEN_PIPE)
			tokens = parse_tokens_helper(cmd, tokens, &last_file, file, env);
		if (tokens && tokens->type == TOKEN_PIPE)
			parse_tokens_utils(&file, &tokens, &last_file, &cmd);
	}
	return (start);
}