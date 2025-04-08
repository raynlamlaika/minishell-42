
#include"minishell.h"

void append_token(t_token **head, t_token **last, t_token_type type, char *value)
{
	t_token *new = malloc(sizeof(t_token));

	new->type = type;
	if (value)
	new->value = strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
		(*last)->next = new;
	*last = new;
}

void handle_quotes(t_token **head, t_token **last, char *input, int *i, char quote) 
{
	int start = *i;

    while (input[*i])
    { 
        (*i)++;
        if (input[*i] && strchr("\n", input[*i]))
            break;
    }
    char *word = strndup(input + start, *i - start);
    append_token(head, last, TOKEN_WORD, word);
    (*i)--;
}

void handle_word(t_token **head, t_token **last, char *input, int *i)
{
    int start = *i;
    int j = *i;
    int in_quotes = 0;
    char quote_char = 0;

    while (input[j] && (in_quotes || (!strchr(" |<>\n", input[j]))))
    {
        if ((input[j] == '"' || input[j] == '\''))
        {
            if (!in_quotes)
            {
                in_quotes = 1;
                quote_char = input[j];
            }
            else if (input[j] == quote_char)
            {
                in_quotes = 0;
            }
        }
        j++;
    }
    char *word = strndup(input + start, j - start);
    append_token(head, last, TOKEN_WORD, word);
    *i = j - 1;
}

t_token *lexer(char *input)
{
	int i = 0;
	t_token *head = NULL;
	t_token *last = NULL;

    while (input[i] && input[i] != '\n')
    {
        if (input[i] == ' ')
            ;
        else if (input[i] == '|')
            append_token(&head, &last, TOKEN_PIPE, "|");
        else if (input[i] == '<' && input[i + 1] == '<')
            append_token(&head, &last, TOKEN_HEREDOC, "<<"), i++;
        else if (input[i] == '>' && input[i + 1] == '>')
            append_token(&head, &last, TOKEN_APPEND, ">>"), i++;
        else if (input[i] == '<')
            append_token(&head, &last, TOKEN_REDIR_IN, "<");
        else if (input[i] == '>')
            append_token(&head, &last, TOKEN_REDIR_OUT, ">");
        else if (input[i] == '"')
            handle_quotes(&head, &last, input, &i, '"');
        else if (input[i] == '\'')
            handle_quotes(&head, &last, input, &i, '\'');
        else
            handle_word(&head, &last, input, &i);
        i++;
    }
    append_token(&head, &last, TOKEN_EOF, NULL);
    return (head);
}

int main(int ac,char **av,char**env) {
	char *line = NULL;
	size_t len = 10;
	ssize_t nread;
	t_cmd *cmd = NULL;

	int i = 1;
	while(i)
	{
		line = readline("minishell$");
		if (!line) 
		{
			perror("readline");
			free(line);
			return 1;
		}
		t_token *tokens =lexer(line);
		syntax(tokens);
		parse_tokens(tokens);
        // while (tokens)
        // {
        //     printf("this is the tokens :%s\n", tokens->value);
        //     tokens = tokens->next;
        // }
		// while (tokens)
		// {
		// 	cmd = malloc(sizeof(t_cmd));
		// 	if (tokens->type == TOKEN_WORD)
		// 		;
		// 	else if (tokens->type == TOKEN_WHITESPACE)
		// 		;
		// 	else if (tokens->type == TOKEN_REDIR_OUT)
		// 		;
		// 	else if (tokens->type == TOKEN_REDIR_IN)
		// 		;
		// 	else if (tokens->type == TOKEN_QUOTE)
		// 		;
		// 	else if (tokens->type == TOKEN_PIPE)
		// 		;
		// 	else if (tokens->type == TOKEN_HEREDOC)
		// 		;
		// 	else if (tokens->type == TOKEN_EOF)
		// 		;
		// 	else if(tokens->type == TOKEN_DQUOTE)
		// 		;
		// 	else if (tokens->type == TOKEN_APPEND)
		// 		;
		// 	tokens = tokens->next;
		// }
		if(i >= 4)
			break;
		i++;
	}
	free(line);
	return 0;
}
