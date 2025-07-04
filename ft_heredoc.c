/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:31:33 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/19 20:30:23 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(t_file *files)
{
	if (!files)
		return ;
	while (files)
	{
		if (files->here_doc != -1 && files->here_doc != 0)
		{
			close(files->here_doc);
			files->here_doc = -1;
		}
		files->here_doc = -1;
		files = files->next;
	}
}

static int	lines(int *fd, char *limiter, int flag, t_env *env)
{
	char	*next;
	char	*tmp;

	while (1)
	{
		g_here_doc_helper = 42;
		(1) && (next = readline("here_doc >> "), tmp = next);
		if (!next || g_here_doc_helper == 20)
		{
			if (g_here_doc_helper != 20)
				print_error_arg("minishell: \
unexpected EOF while looking for matching `", limiter, "`\n");
			return (0);
		}
		if (pick_limiter(next, limiter) == 0)
			break ;
		next = ft_strjoin(next, "\n");
		free(tmp);
		if (ft_strchr(next, '$') && flag == 0)
			next = take_token_doc(next, env, 0);
		write(fd[1], next, ft_strlen(next));
	}
	free(tmp);
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
	result = ft_malloc(sizeof(char) * (ft_strlen(exp) + 1), 1);
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
		if (pipfd[0] != -1)
		{
			close(pipfd[0]);
			pipfd[0] = -1;
		}
		pipfd[0] = -1;
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
	i = lines(pipfd, str, expande, env);
	if (i == 0)
		return (helper_check(pipfd, file), close(pipfd[1]), 0);
	return (helper_check(pipfd, file), close(pipfd[1]), pipfd[0]);
}
