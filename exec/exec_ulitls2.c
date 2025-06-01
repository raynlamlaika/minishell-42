/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ulitls2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:57:31 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/01 13:34:59 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	inf_helper(int *inf, t_file *files)
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
			if (files->infile[0] == '\0')
			{
				fprintf(stderr, "minishell: \
%s: No such file or directory\n", files->infile);
				*inf = -5;
				return (0);
			}
			else
			{
				perror("minishell");
				*inf = -5;
				return (0);
			}
			return (0);
		}
	}
	return (1);
}

int	helper_outf(int *outf, t_file *files)
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
			fprintf(stderr, "minishell: %s: \
No such file or directory\n", files->outfile);
			*outf = -5;
			return (0);
		}
		else
		{
			perror("minishell");
			*outf = -5;
			return (0);
		}
	}
	return (1);
}

void	get_redirections(int*inf, int *outf, t_cmd*full)
{
	t_file	*files;

	files = full->file;
	*inf = -1;
	*outf = -1;
	while (files)
	{
		if (files->infile || files->here_doc)
			if (inf_helper(inf, files) == 0)
				return ;
		if (files->outfile)
			if (helper_outf(outf, files) == 0)
				return ;
		files = files->next;
	}
}
