
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
    // here i need to handel cases like 'e''c''h''o' ""'"'''""""""""''''
    int start = ++(*i);
    while (input[*i] && input[*i] != quote)
        (*i)++;
    char *quoted_str = strndup(input + start, *i - start);
    append_token(head, last, TOKEN_WORD, quoted_str);
}

void handle_word(t_token **head, t_token **last, char *input, int *i) 
{
    int start = *i;

    while (input[*i] && !strchr(" |<>\"", input[*i]))  // Stop at spaces or operators
        (*i)++;
    char *word = strndup(input + start, *i - start);
    append_token(head, last, TOKEN_WORD, word);
    (*i)--;  // Adjust index
}



t_token *lexer(char *input)
{
    int i = 0;
    t_token *head = NULL;
    t_token *last = NULL;

    while (input[i])
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
            handle_quotes(&head, &last, input, &i, '"');  // Handle double quotes
        else if (input[i] == '\'' || input[i] == '\"')
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
    printf("minishell$");
    int i = 1;
    while(i)
    {
       
        nread = getline(&line, &len, stdin);
        if (nread == -1) 
        {
            perror("getline");
            free(line);
            return 1;
        }
        printf("the full line after parssing %s\n",line);
        t_token *tokens =lexer(line);
        while (tokens)
        {
            printf("Token Type: %d, Value: %s\n", tokens->type, tokens->value);
            tokens = tokens->next;
        }
        printf("minishell$");
        if(i >= 4)
            break;
        i++;
    }
    free(line);
    return 0;
}
