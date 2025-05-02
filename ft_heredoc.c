/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:31:33 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/02 10:47:08 by rlamlaik         ###   ########.fr       */
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

static void	lines(int fd, char *limiter)
{
    char	*next;

    while (1)
    {
        write(1, "pipex_heredoc >> ", 17);
        next = get_next_line(0);
        if (!next)
            break ;
        if (search_search(next, limiter) == 0)
        {
            free(next);
            break ;
        }
        write(fd, next, ft_strlen(next));
        free(next);
    }
}

int heredoc(char *limiter)
{
    int pipfd[2];

    if (pipe(pipfd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    lines(pipfd[1], limiter);
    close(pipfd[1]);
    return pipfd[0];
}

