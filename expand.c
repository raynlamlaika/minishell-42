/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 04:32:41 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/11 20:09:21 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_token *create_token(char *value)
// {
//     t_token *new = NULL;
//     new  = ft_malloc(sizeof(t_token), 1);
//     if (!new)
//         return NULL;

//     new->value = ft_strdup(value);
//         return NULL;
//     new->type = TOKEN_WORD;
//     new->next = NULL;
//     return new;
// }

t_token *create_token(char *value)
{
    t_token *new = NULL;
    
    new = ft_malloc(sizeof(t_token), 1);
    if (!new)
        return NULL;
    new->value = ft_strdup(ft_handel_qoute(value));
    // if (!new->value) {
    //     free(new);  // Don't forget to free the allocated token if strdup fails
    //     return NULL;
    // }
    new->type = TOKEN_WORD;
    new->next = NULL;
    return new;
}
void insert_token_after(t_token *current, t_token *new_token)
{
    if (!current || !new_token)
        return;
    t_token *old_next = current->next;
    current->next = new_token;
    new_token->next = old_next;
}
// void insert_token_after(t_token *current, t_token *new_token)
// {
//     if (!current || !new_token)
//         return;
//     new_token->next = current->next;
//     current->next = new_token;
// }

int	ft_strcmp(const char *s1, const char *s2)
{
    if (!(*s1) || !(*s2))
        return(1);
    while (*s1 && *s1 == *s2)
    {

        s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
char *ft_replace(char *check, t_env *env)
{
    while (env)
    {
        if (ft_strcmp(env->key, check) == 0)
            return ft_strdup(env->value);
        env = env->next;
    }
    return ft_strdup("");
}

char *ft_substr(char *s, unsigned int start, size_t end)
{
    if (!s || end <= start)
        return NULL;

    size_t slen = ft_strlen(s);
    if (start >= slen)
        return ft_strdup("");

    if (end > slen)
        end = slen;

    size_t len = end - start;

    char *substr = ft_malloc((len + 1), 1); // allocate exact space
    if (!substr)
        return NULL;

    size_t i = 0;
    while (i < len)
        substr[i++] = s[start++];
    substr[i] = '\0';

    return substr;
}

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || (c >= '0' && c <= '9'));
}


char *ft_strjoin_free(char *s1, char *s2)
{
    char *res = ft_strjoin(s1, s2);
    return res;
}

void replace_token(char **token_value, char *exp)
{
    if (!token_value || !exp)
        return;
    *token_value = ft_strdup(exp);
    if (!*token_value)
    {
        perror("replace_token: strdup failed");
        exit(EXIT_FAILURE);
    }
}

char* ft_take(char* string ,int *i, t_env *env)
{
    int help;
    char *search;
    char * result;
    
    help = *i;
    while (ft_isalpha(string[help]) || ft_isdigit(string[help]))
    {
        help++;
    }
    search = ft_substr(string, *i, help);
    result = ft_replace(search, env);
    *i = help;
    return (result);
}



int expnd_size(char* string, int *i, t_env *env)
{
    int help;
    char *search;
    char *result;
    int size;
    
    help = *i;
    while (ft_isalpha(string[help]) || ft_isdigit(string[help]))
        help++;
    search = ft_substr(string, *i, help);
    result = ft_replace(search, env);
    size = ft_strlen(result);
    *i = help;
    return (size);
}

int size_help(char *string, t_env *env)
{
    int size = 0;
    int quote = 0;
    int i = 0;

    while (string[i])
    {
        if ((string[i] == '\'' || string[i] == '"') && quote == 0)
            quote = string[i];
        else if (string[i] == quote)
            quote = 0;  
        if (string[i] == '$' && quote != '\'')
        {
            i++;
            if (ft_isalpha(string[i]) || ft_isdigit(string[i]) || string[i] == '_')
            {
                size += expnd_size(string, &i, env);
            }
            else
            {
                if (string[i] == '$' || string[i] == '?')
                    size += 1;
            }
        }
        else
        {
            size++;
            i++;
        }
    }
    return size;
}

char* take_token(char *string, t_env *env)
{
    int i = 0, quote = 0, a= 0;
    int size = size_help(string, env);
    char* result = ft_malloc(size + 1, 1);
    char *tmp = NULL;
    int t;
    if (!result)
        write(2, "eroor\n", 6);

    while (string[i])
    {
        if ((string[i] == '\'' || string[i] == '"') && quote == 0)
            quote = string[i];
        else if (string[i] == quote)
            quote = 0;
        if (string[i] == '$' && quote != '\'')
        {
            i++;
            if(ft_isalpha(string[i]) || ft_isdigit(string[i]) || string[i] == '_')// dijjet alpha _
            {
                t = 0;
                tmp = ft_take(string, &i, env);
                while(tmp[t])
                    result[a++] = tmp[t++];
          
            }
            else
            {
                if (string[i] == '$' || string[i] == '?')
                    result[a++] = '$';
                
            }
        }
        else
            result[a++] = string[i++];
    }
    result[a] = '\0';
    return(result);
}

char *take_replace(int i, char *input, int *help, t_env *env)
{
    int start = i + 1;
    int len = 0;

    if (!ft_isalpha(input[start]) && input[start] != '_') {
        *help = start;
        return ft_strdup("$");
    }
    while (ft_isalnum(input[start + len]) || input[start + len] == '_')
        len++;
    *help = start + len;
    char *key = ft_substr(input, start, len);
    char *val = ft_strdup("");
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
        {
            val = ft_strdup(env->value);
            break;
        }
        env = env->next;
    }
    return val;
}

int split_allocation(char *result)
{
    int size = 0;
    int i = 0;
    int n = 0;
    int m = 0;
    int y = 0;
    
    while (result[i])
    {
        if (result[i] == '\"' && m % 2 == 0)
        {
            n++;
            y = n;
        }
        if (result[i] == '\'' && n % 2 == 0)
        {
            m++;
            y = m;
        }
        size++;
        i++;
        if (y % 2 == 0 && result[i] == ' ')
        {
            while (result[i] == ' ')
                i++;
            break;
        }
    }
    return size;
}

char *s_split(char *result, t_token *token)
{
    char *str;
    int i = 0;
    int n = 0;
    int m = 0;
    int y = 0;
    int a= 0;
    int size = split_allocation(result);
    
    int add = 0;
    str = ft_malloc(size + 1, 1);

    while (result[i])
    {
        a = 0;
        while(result[i])
        {
            if(result[i] == '\"' && m % 2 == 0)
            {
                n++;
                y = n;
            }
            if(result[i] == '\'' && n % 2 == 0)
            {
                m++;
                y = m;
            }
            if (y % 2 != 0)
            {
                str[a++] = result[i++];
            }
            else
            {
                str[a++] = result[i++];
                if(result[i] == ' ')
                {
                    while(result[i] == ' ')
                        i++;
                    break ;
                }
            }
        }
        str[a] = '\0';
        if (add == 0)
        {
            token->value = ft_handel_qoute(str);
            add = 1;
        }
        else
        {
            t_token *new_node = create_token(str);
            insert_token_after(token, new_node);
            token = new_node; // Move to the new node
        }
        
        if (result[i]) // Only allocate if more tokens coming
        {
            size = split_allocation(result + i);
            str = ft_malloc(size + 1, 1);
        }
    }
    return result;
}

void	ptt(t_token *head)
{
	t_token	*current = head;

	while (current)
	{
		printf("Type: %d\n", current->type);
		printf("Value: %s\n", current->value);
		printf("Quoted: %s\n", current->quoted ? "Yes" : "No");
		printf("---------------------\n");
		current = current->next;
	}
}

void expand(t_token *token, t_env *env)
{

    char *cleaned;
    while (token && token->value)
    {
        if (ft_strchr(token->value, '$'))
        {
            char * result = take_token(token->value, env);
            s_split(result, token);//
            
        }
        else
        {
            cleaned = handling_qoutes(token->value, '"');
            char *final = handling_qoutes(cleaned, '\'');
            // free(cleaned);

            replace_token(&token->value, final);
            // free(final);
        }
        token = token->next;
    }
    // ptt(head);
}
