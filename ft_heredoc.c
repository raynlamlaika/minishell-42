/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:31:33 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/10 08:14:10 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
        
static int	search_search(char *next, char *limiter)
{
    int		result;

    result = ft_strcmp(next, limiter);
    return (result);
}

char *expnd_heredoc(char *input, t_env *env)
{
    int i = 0;
    int start = 0;
    char *result = ft_strdup("");

    while (input[i])
    {
        if (input[i] == '$')
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

    return (result);
}

static void	lines(int fd, char *limiter, int flag, t_env *env)
{
    char	*next;

    while (1)
    {
        next = readline("here_doc >> ");
        if (!next)
            break ;
        if (ft_strchr(next, '$') && flag == 0)
            next = expnd_heredoc(next, env);
        if (search_search(next, limiter) == 0)
            break ;
        write(fd, next, ft_strlen(next));
    }
}

char *ft_handel_qoute(char *exp)
{
    int i = 0;
    int j = 0;
    int sing_flag = 0;
    int double_flag = 0;
    char *result = ft_malloc(sizeof(char) * (strlen(exp) + 1), 1); // be sure to free this later

    if (!result)
        return NULL;

    while (exp[i])
    {
        if (exp[i] == '"' && sing_flag % 2 == 0)
            double_flag++;
        else if (exp[i] == '\'' && double_flag % 2 == 0)
            sing_flag++;
        else
            result[j++] = exp[i];
        i++;
    }
    result[j] = '\0';
    return (result);
}

int heredoc(char *limiter, t_env *env)
{
    int pipfd[2];
    char *str = NULL;
    int expande;

    expande = 0;
    int i = 0;
    while( limiter[i])
    {
        if (limiter[i] == '\'' || limiter[i] == '"')
        {
            expande =  1;
            break ;
        }
        i++;
    }
    str = ft_handel_qoute(limiter);
    // printf("limiter :%s\n", str);
    if (pipe(pipfd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    lines(pipfd[1], str, expande, env);
    close(pipfd[1]);
    return pipfd[0];
}

