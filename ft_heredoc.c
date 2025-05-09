/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:31:33 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/09 21:08:53 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
        
static int	search_search(char *next, char *limiter)
{
    char	*full_limiter;
    int		result;

    full_limiter = ft_strjoin(limiter, "\n");
    if (!full_limiter)
        return (exit(1), 1);
    result = ft_strncmp(next, full_limiter, ft_strlen(full_limiter));
    free(full_limiter);
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
        write(1, "pipex_heredoc >> ", 17);
        next = get_next_line(0);
        if (!next)
            break ;
        if (ft_strchr(next, '$') && flag == 0)
            next = expnd_heredoc(next, env);
        if (search_search(next, limiter) == 0)
        {
            free(next);
            break ;
        }
        write(fd, next, ft_strlen(next));
        free(next);
    }
}

int heredoc(char *limiter, t_env *env)
{
    int pipfd[2];
    char *str;
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
    // str = ft_handel_qoute(limiter);
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

