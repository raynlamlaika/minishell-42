/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ulitls2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:57:31 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/27 02:09:29 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	get_redirections(int *inf, int *outf, t_cmd* full)
{
	t_file	*files;

	files = full->file;
	*inf = -1;
	*outf = -1;
	while (files)
	{
		if (files->infile || files->here_doc)
		{
			if (*inf > -1)
				close(*inf);
			if (files->here_doc)
				*inf = files->here_doc;
			else
			{
				*inf = open(files->infile, O_RDONLY);
				if (*inf < 0)
				{
					fprintf(stderr,"minishell: %s: No such file or directory\n", files->infile);
					*inf = -5;
					break ;
				}
			}
		}
		if (files->outfile)
		{
			if (*outf > -1)
				close(*outf);
			if (files->append)
				*outf = open(files->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				*outf = open(files->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (*outf < 0)
			{
				if (files->outfile[0] == '\0')
				{
					fprintf(stderr,"minishell: %s: No such file or directory\n", files->outfile);
					break ;
				}
				else
				{
					fprintf(stderr, "minishell: %s: Permission denied\n", files->outfile);
					*outf = -5;
					break ;
				}
			}
		}
		files = files->next;
	}
}

int	pipecheck(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		fprintf(stderr, "minishell :`Pipe` can't open\n");
		return (0);
	}
	return(1);
}

int	forkfaild(pid_t pid, int*pipefd)
{
	int i = 0;
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		i++;
	}
	return (i);
}
