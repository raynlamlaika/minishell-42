#include "minishell.h"

char	*ft_strndup(char *s1, int n)
{
	int		i;
	char	*s2;

	s2 = malloc((1 + n) * (sizeof(char)));
	if (!s2)
	return (NULL);
	i = 0;
	while (i < n && s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int is_redirection(t_token *tokens)
{
	return (tokens->type == TOKEN_HEREDOC || tokens->type == TOKEN_APPEND ||
		tokens->type == TOKEN_REDIR_OUT || tokens->type == TOKEN_REDIR_IN ||
		tokens->type == TOKEN_PIPE);
}

void syntax(t_token *tokens)
{
	if (!tokens || tokens->type == TOKEN_PIPE)
	{
		printf ("error syntax\n");
		exit(1);
	}
	while(tokens)
	{
		if (is_redirection(tokens))
		{
			if (!tokens->next)
			{
				printf("syntax error\n");
				exit(1);
			}
			if (tokens->next->type == TOKEN_PIPE)
			{
				printf ("syntax error\n");
				exit (1);
			}
			if (is_redirection(tokens->next))
			{
				printf ("syntax error\n");
				exit(1);
			}
		}
		if (tokens->type == TOKEN_PIPE)
		{
			if (tokens->next->type == TOKEN_EOF)
			{
				printf("syntax errr\n");
				exit(1);
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
	s = (char *)malloc(size * count);
	if (!s)
		return (NULL);
	while (i < (size * count))
	{
		s[i] = 0;
		i++;
	}
	return (s);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*s2;

	i = 0;
	s2 = malloc((ft_strlen(s1) + 1) * (sizeof(char)));
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

void add_arg(t_cmd *type, char *value)
{
	int count = 0;
	int i = 0;
	int j = 0;
	char **new_args;

	if (type->args)
	{
		while (type->args[count])
			count++;
	}
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return;
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

void print_cmds(t_cmd *cmd)
{
	int i;
	int num = 1;
	while (cmd)
	{
		printf("\n--- Command %d ---\n", num++);
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
					file->infile = tokens->next->value;
				else
					last_file->infile = tokens->next->value;
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
		}
	}
	print_cmds(start);
	return (start);
}



