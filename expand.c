/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 04:32:41 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/04/29 19:55:12 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
int ft_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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
	string = (char *)ft_malloc((1 + len) * sizeof(char), 1);
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

char* ft_replace(char* check, t_env *env, int *help)
{
    (void)help;
    if (!ft_isdigit(check[0]) &&  !ft_isalpha(check[0]))
    {
        return (ft_strjoin("$",check));
    }
    if (ft_isdigit(check[0]) || check[0] == '\0')
    {
        if (!check[1])
            return (ft_strdup(""));
        return (ft_strdup(check + 1));
    }
    while(env)
    {
        if (ft_strcmp(env->key, check) == 0)
        {
            free(check);
            return(env->value);
        }
        env = env->next;
        if (!env->next)
            return (NULL);
    }
    return (NULL);
}

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (1);
	return (0);
}
char *take_replace(int i, char *input, int *help, t_env *env)
{
    char* check;
    int  o = i;
    int alloc = 0;
    int y = 0;

    o++;
    i++;
    while (ft_isalnum(input[o]))
    {
        alloc++;
        o++;
    }
    check =  ft_malloc(alloc + 1, 1);
    while (y < alloc && input[i])
    {
        check[y] =  input[i];
        y++;
        i++;
    }
    check[y] = '\0';
    *help = i;
    char *tt = ft_replace(check, env, help);
    if (tt)
        return (tt);
    return (NULL);
}
char *take_first(int i, char *input)
{
    int back = 0;
    char *ppp = ft_malloc(i, 1);
    while (i > back && input[back])
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
    last = ft_malloc(alloc, 1);
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

char *take_expand(char *input, t_env *env)
{
    int i = 0;
    int help;
    char quote = 0;
    char *result = ft_strdup("");

    while (input[i])
    {
        
        if ((input[i] == '\'' || input[i] == '"') && quote == 0)
        {
            quote = input[i++];
            char *quoted = ft_strdup(""); // store inside the quotes
            
            while (input[i] && input[i] != quote)
            {
                if (input[i] == '$' && quote != '\'')
                {
                    char *repl = take_replace(i, input, &help, env);
                    // char *before = ft_substr(input, i, help - i);
                    quoted = ft_strjoin(quoted, repl);
                    i = help;
                }
                else
                {
                    char *c = ft_substr(input, i, 1);
                    quoted = ft_strjoin(quoted, c);
                    i++;
                }
            }
            if (input[i] == quote) i++; // skip ending quote
            
            if (quote == '\'') // preserve single quotes
            result = ft_strjoin(result, ft_strjoin("'", ft_strjoin(quoted, "'")));
            else
            result = ft_strjoin(result, quoted);
            
            quote = 0;
        }
        else if (input[i] == '$' && quote != '\'')
        {
            char *repl = take_replace(i, input, &help, env);
            result = ft_strjoin(result, repl);
            i = help;
        }
        else
        {
            char *c = ft_substr(input, i, 1);
            result = ft_strjoin(result, c);
            i++;
        }
    }

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

char *ft_strcpy(char *dest, const char *src)
{
    int i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

void    expand(t_token *token, t_env *env)
{
    char *exp;
    char* helper;

    while (token->value)
    {
        if (ft_strchr(token->value, '$'))
        {
            exp = take_expand(token->value, env);
            if (exp)
                replace_token(&token->value, exp);
        }
        else if ((ft_strchr(token->value, '"') || ft_strchr(token->value, '\'')) && !ft_strchr(token->value, '$'))
        {
            if (ft_strchr(token->value, '\"'))
                helper = handling_qoutes(token->value,'"');
            if (ft_strchr(token->value, '\''))
                helper = handling_qoutes(token->value,'\'');
            replace_token(&token->value, helper);
        }
        token = token->next;
    }
}


// need to split expect if there is echo aftr