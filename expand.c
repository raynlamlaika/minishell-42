/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 04:32:41 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/09 20:53:09 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *create_token(char *value)
{
    t_token *new = malloc(sizeof(t_token));
    if (!new)
        return NULL;

    new->value = ft_strdup(value);
    if (!new->value)
    {
        free(new);
        return NULL;
    }
    new->type = TOKEN_WORD;
    // new->quoted = 0;
    new->next = NULL;
    return new;
}

void insert_token_after(t_token *current, t_token *new_token)
{
    if (!current || !new_token)
        return;
    new_token->next = current->next;
    current->next = new_token;
}

int	ft_strcmp(const char *s1, const char *s2)
{
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
        {
            free(check);
            return ft_strdup(env->value);
        }
        env = env->next;
    }
    free(check);
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

    char *substr = malloc(len + 1); // allocate exact space
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
    free(s1);
    if (s2 && s2 != s1)
        free(s2);
    return res;
}

void replace_token(char **token_value, char *exp)
{
    if (!token_value || !exp)
        return;
    free(*token_value);
    *token_value = ft_strdup(exp);
    if (!*token_value)
    {
        perror("replace_token: strdup failed");
        exit(EXIT_FAILURE);
    }
}

int size_take_expand(char*string ,int  size, t_env *env)
{
    int i;
    int help;
    i = 0;
    help = 0; 
    while (ft_isalpha(string[size]))
    {
        i++;
        size++;
    }
    help = size - i;
    char * sub = ft_substr(string, help, size);
    return (12);
}
int ft_size_help(char *string, t_env *env)
{
    int size;
    int env_size;

    env_size= 0;
    size = 0;
    while(string[size])
    {
        if (string[size] == '$')
        {
            size++; //skip the dollar sign
            if (ft_isalpha(string[size]))
                env_size = size_take_expand(string , size, env);
        }
        size++;
    }
    return size;
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
    return (result); // ls"$a"$a  ls"youssef    lagzouli"youssef lagzouli
}


char* take_token(char *string, t_env *env)
{
    int i = 0, quote = 0, a= 0;
    char* result = malloc(20); //(ft_size_help(string, env));
    char *tmp;
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
    // printf("the resu %s\n", result);
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
    free(key);
    return val;
}

char *s_split(char *result, t_token *token)
{
    char *str;
    int i = 0;
    int n = 0;
    int m = 0;
    int y = 0;
    int a= 0;
    str = malloc(77);

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
        printf("-------{%s}\n",str);
        
        str = malloc(42);
    }
    // exit(1);
    return result;
}






void expand(t_token *token, t_env *env)
{
    char *exp;
    char *cleaned;
    int i =0;
    while (token && token->value)
    {
        if (ft_strchr(token->value, '$'))
        {
            char * result = take_token(token->value, env);
            s_split(result, token);
            
        }
        else
        {
            cleaned = handling_qoutes(token->value, '"');
            char *final = handling_qoutes(cleaned, '\'');
            free(cleaned);

            replace_token(&token->value, final);
            free(final);
        }
        token = token->next;
    }
}
