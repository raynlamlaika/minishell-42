/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ulitls2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:57:31 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/19 09:35:33 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// void get_redirections(int *inf, int *outf, t_cmd* full)
// {	
// 	t_file* files;

// 	files = full->file;
// 	*inf = -1;
// 	*outf = -1;
// 	while(files)
// 	{
// 		if(files->infile || files->here_doc)
// 		{
// 			if (files->here_doc)
// 				*inf = files->here_doc;
// 			else
// 			{
// 				*inf = open(files->infile, O_RDONLY);
// 				if (*inf < 0)
// 				{
// 					printf("minishell:%s  : No such file or directory\n", files->infile);
// 					*inf = -5;
// 				}
// 				files = files->next;
// 				if (files)
// 				{
// 					if (files->infile != NULL)
// 					{
// 						if (*inf)
// 							close(*inf);
// 						if (files->here_doc)
// 							close(files->here_doc);
// 					}
// 				}
// 			}
// 		}
// 		if (files)
// 		{			
// 			if(files->outfile)
// 			{
// 				if(files->append)
// 					*outf =  open(files->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 				else
// 					*outf =  open(files->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 				if (*outf < 0)
// 				{
// 					printf("minishell: %s: Permission denied\n", files->outfile);
// 					*outf = -5;
// 				}
// 				files = files->next;
// 				if (files)
// 					if (files->outfile != NULL)
// 						if(*outf)
// 							close(*outf);
// 			}
// 			else
// 				files = files->next;
// 		}
// 	}
// }


void get_redirections(int *inf, int *outf, t_cmd* full)
{
    t_file* files = full->file;
    *inf = -1;
    *outf = -1;

    while (files)
    {
        // Handle input redirections
        if (files->infile || files->here_doc)
        {
            if (*inf != -1)
                close(*inf);  // Close previous input file if already open

            if (files->here_doc)
                *inf = files->here_doc;  // Use here_doc fd directly
            else
            {
                *inf = open(files->infile, O_RDONLY);
                if (*inf < 0)
                {
                    printf("minishell: %s: No such file or directory\n", files->infile);
                    *inf = -5;
					break ;
                }
            }
        }

        // Handle output redirections
        if (files->outfile)
        {
            if (*outf != -1)
                close(*outf);  // Close previous output file if already open

            if (files->append)
                *outf = open(files->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
            else
                *outf = open(files->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if (*outf < 0)
            {
                printf("minishell: %s: Permission denied\n", files->outfile);
                *outf = -5;
				break ;
            }
        }

        files = files->next;
    }
}


void	pipecheck(int *pipefd)
{
	if (pipe(pipefd) == -1)
		printf("minishell :`Pipe` can't open\n");
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
