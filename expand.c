/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 04:32:41 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/02 10:47:40 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*string;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (start >= i)
		return (ft_strdup(""));
	if (i - start < len)
		len = i - start;
	string = (char *)malloc((1 + len) * sizeof(char));
	if (!string)
		return (NULL);
	i = 0;
	while (s[start] && len > 0)
	{
		string[i++] = s[start++];
		len--;
	}
	string[i] = '\0';
	return (string);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
char* ft_replace(char* check, t_env *env)
{
    while(env->key)
    {
        if (ft_strncmp(env->key, check, ft_strlen(check)) == 0)
        {
            free(check);
            return(env->value);
        }
        env = env->next;
    }
    return(NULL);
}

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (1);
	return (0);
}

// char *take_replace(int i, char *input, int *help, t_env *env)
// {
//     char* check;
//     int  o = i;
//     int alloc = 0;
//     int y = 0;
//     o++;
//     i++;
//     while (ft_isalnum(input[o]))
//     {
//         alloc++;
//         o++;
//     }
//     check =  malloc(alloc);
//     while (y < alloc)
//     {
//         check[y] =  input[i];
//         y++;
//         i++;
//     }
//     *help = i;
//     char *tt = ft_replace(check, env);
//     if (tt)
//         return (tt);
//     return(check);
// }

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

char *take_first(int i, char *input)
{
    int back = 0;
    char *ppp = malloc(i);
    while (i > back)
    {
        ppp[back] = input[back];
        back++;
    }
    ppp[back] = '\0';
    return(ppp);
}

char *last_t(int help, char *input)
{
    int alloc = 0;
    char *last;
    int i =  help;
    
    while(input[help])
    {
        alloc++;
        help++;
    }
    last =malloc(alloc);
    alloc = 0;
    while (input[i])
    {
        last[alloc] = input[i];
        alloc++;
        i++;
    }
    return(last);
    
}

char* ft_can(char *rplt, char* first, char*last)
{
    char *uuu;
    char*res;
    
    uuu = ft_strjoin(first, rplt);
    res = ft_strjoin(uuu, last);
    return (res);
}

char *ft_strjoin_free(char *s1, char *s2)
{
    char *res = ft_strjoin(s1, s2);
    free(s1);
    if (s2 != NULL && s2 != s1) free(s2); // only if s2 was dynamically allocated
    return res;
}
char *remove_outer_quotes(char *s)
{
    if (!s || ft_strlen(s) < 2)
        return ft_strdup(s);

    char first = s[0];
    char last = s[ft_strlen(s) - 1];

    if ((first == '\'' && last == '\'') || (first == '"' && last == '"'))
        return ft_substr(s, 1, ft_strlen(s) - 2);

    return ft_strdup(s);
}


char *take_expand(char *input, t_env *env)
{
    int i = 0;
    int start = 0;
    char quote = 0;
    char *result = ft_strdup("");

    while (input[i])
    {
        if ((input[i] == '\'' || input[i] == '"') && quote == 0)
            quote = input[i];
        else if (input[i] == quote)
            quote = 0;

        if (input[i] == '$' && quote != '\'') // skip $ expansion in single quotes
        {
            if (i > start)
                result = ft_strjoin_free(result, ft_substr(input, start, i - start));

            int help;
            char *repl = take_replace(i, input, &help, env);
            result = ft_strjoin_free(result, repl);
            i = help;
            start = i;
        }
        else
            i++;
    }

    if (i > start)
        result = ft_strjoin_free(result, ft_substr(input, start, i - start));

    return result;
}



void replace_token(char **token_value, char *exp)
{
    if (!token_value || !exp)
        return;
    if (*token_value)
        free(*token_value);
    *token_value = ft_strdup(exp);
    if (!*token_value) {
        perror("replace_token: strdup failed");
        exit(EXIT_FAILURE);
    }
}

void expand(t_token *token, t_env *env)
{
    char *exp;
    char *cleaned;

    while (token && token->value)
    {
        if (ft_strchr(token->value, '$'))
        {
            exp = take_expand(token->value, env);
            if (exp)
            {
                // cleaned = handling_qoutes(exp, '"');
                // char *final = handling_qoutes(cleaned, '\'');
                // free(cleaned);
                replace_token(&token->value, exp);
                // free(final); // replace_token made a copy
                free(exp);
            }
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
