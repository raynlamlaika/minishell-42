/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ulitls2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:57:31 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/18 19:02:59 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_inf(int *inf)
{
	if (*inf > -1)
		close(*inf);
}

int	inf_helper(int *inf, t_file *files)
{
	close_inf(inf);
	if (files->here_doc)
		*inf = files->here_doc;
	else if (ft_strcmp(files->outfile, "/dev/stdin"))
	{
		*inf = open(files->infile, O_RDONLY);
		if (*inf < 0)
		{
			if (files->infile[0] == '\0')
			{
				print_error_arg("minishell: ", \
files->infile, " : No such file or directory\n");
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
	if (ft_strcmp(files->outfile, "/dev/stdout") == 0)
		return (1);
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
			print_error_arg("minishell: ", files->outfile, \
" :No such file or directory\n");
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
		{
			if (inf_helper(inf, files) == 0)
				return ;
		}
		if (files->outfile)
		{
			if (helper_outf(outf, files) == 0)
				return ;
		}
		files = files->next;
	}
}
