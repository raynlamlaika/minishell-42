/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:31:33 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/04/30 16:30:05 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	last_cmmd(char **av, char **paths, int *pipfd)
// {
    // 	int		outfile;
    // 	char	**cmd;
    // 	char	*path;
    
    // 	outfile = open(av[5], O_CREAT | O_APPEND | O_RDWR, 0644);
    // 	if (outfile == -1)
    // 		return (perror("pipex"), 0);
    // 	if (dup2(pipfd[0], STDIN_FILENO) == -1)
    // 		return (close(pipfd[0]), close(outfile), 0);
    // 	if (dup2(outfile, STDOUT_FILENO) == -1)
    // 		return (close(outfile), close(pipfd[0]), 0);
    // 	close(pipfd[0]);
    // 	close(outfile);
    // 	cmd = split(av[4]);
    // 	path = pick(paths, cmd[0]);
    // 	if (!path)
    // 		return (perror("pipex"), clean_2(cmd), 0);
    // 	if (execve(path, cmd, NULL) == -1)
    // 	{
        // 		perror("pipex");
        // 		clean_2(cmd);
        // 		exit(1);
        // 	}
        // 	return (0);
        // }
        
        // if (ac < 6)
        // 	return (perror("pipex"), 1);
        // limiter = av[2];
        // if (pipe(pipfd) == -1)
        // 	return (perror("pipe"), 1);
        // lines(pipfd[1], limiter);
        // close(pipfd[1]);
        // if (pipe(newpip) == -1)
        // 	return (perror("pipe"), 1);
        // if (fork() == 0)
        // 	executing(pipfd[0], av[3], paths, newpip[1]);
        // close(pipfd[0]);
        // close(newpip[1]);
        // if (fork() == 0)
        // 	last_cmmd(av, paths, newpip);
        // close(pipfd[0]);
        // close(newpip[0]);
        // close(newpip[1]);
        // clean_2(paths);
        // wait(NULL);
        //}
        
        
        
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

    printf("yooooo\n");
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
        
int	heredoc(char* limiter)
{
    int		pipfd[2];
    int		newpip[2];
    pipe(pipfd);
    printf("passsed\n");
    lines(pipfd[1], limiter);
    close(pipfd[1]);
    if (pipe(newpip) == -1)
        ;//check fail
    else if (pipe(pipfd) == -1)
        return (0);
    return (pipfd[0]);
}
    
    
    
    
    
    
    