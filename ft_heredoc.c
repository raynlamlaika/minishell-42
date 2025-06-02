/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:31:33 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/02 08:22:39 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pick_limiter(char *next, char *limiter)
{
	int	result;

	if (!next[0] && !limiter[0])
		return (0);
	result = ft_strcmp(next, limiter);
	return (result);
}

char	*expnd_heredoc(char *input, t_env *env)
{
	int		help;
	int		i ;
	int		start;
	char	*repl;
	char	*result;

	start = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			if (i > start)
				result = ft_strjoin(result, ft_substr(input, start, i - start));
			repl = take_replace(i, input, &help, env);
			result = ft_strjoin(result, repl);
			i = help;
			start = i;
		}
		else
			i++;
	}
	if (i > start)
		result = ft_strjoin(result, ft_substr(input, start, i - start));
	return (result);
}

void	ft_close(t_file *files)
{
	if (!files)
		return ;
	while (files)
	{
		if (files->here_doc)
			close(files->here_doc);
		files = files->next;
	}
}

static int	lines(int *fd, char *limiter, int flag, t_env *env)
{
	char	*next;

	while (1)
	{
		g_here_doc_helper = 42;
		next = readline("here_doc >> ");
		if (!next || g_here_doc_helper == 20)
		{
			close(fd[0]);
			close(fd[1]);
			return (0);
		}
		if (pick_limiter(next, limiter) == 0)
			break ;
		next = ft_strjoin(next, "\n");
		if (ft_strchr(next, '$') && flag == 0)
			next = take_token(next, env, 0);
		write(fd[1], next, ft_strlen(next));
	}
	return (1);
}

char	*ft_handel_qoute(char *exp)
{
	int		i;
	int		j;
	int		sing_flag;
	int		double_flag;
	char	*result;

	j = 0;
	sing_flag = 0;
	double_flag = 0;
	i = 0;
	result = ft_malloc(sizeof(char) * (strlen(exp) + 1), 1);
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

void	helper_check(int*pipfd, t_file *file)
{
	if (g_here_doc_helper == 20)
	{
		close(pipfd[0]);
		ft_close(file);
	}
}

int	heredoc(char *limiter, t_env *env, t_file *file)
{
	int		pipfd[2];
	char	*str;
	int		expande;
	int		i;

	(1) && (expande = 0, i = 0);
	while (limiter[i])
	{
		if (limiter[i] == '\'' || limiter[i] == '"')
		{
			expande = 1;
			break ;
		}
		i++;
	}
	str = ft_handel_qoute(limiter);
	if (pipe(pipfd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	lines(pipfd, str, expande, env);
	close(pipfd[1]);
	helper_check(pipfd, file);
	return (pipfd[0]);
}
