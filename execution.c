/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:45:49 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/04/27 18:39:08 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void takes_cmds(t_cmd *cmd_list)
{
    int cmd_index = 0;
    int i;
    while (cmd_list)
    {
        printf("Command # %d:\n", cmd_index);
        t_file *file = cmd_list->file;
        while (file)
        {
            if (file->infile)
                printf("  Infile:  %s\n", file->infile);
            if (file->outfile)
                printf("  Outfile: %s %s\n",
                       file->append ? "(append)" : "(truncate)",
                       file->outfile);
            file = file->next;
            
		    printf("append: %d\n", cmd_list->file->append);
		    i = 0;
		    while (cmd_list->args && cmd_list->args[i])
		    {
			    printf("arg[%d]: %s\n", i, cmd_list->args[i]);
			    i++;
		    }
        }

        cmd_list = cmd_list->next;
        cmd_index++;
    }
}

char **takepaths(t_env *env_lnk)
{
	char	**path;
	char	*take = NULL;
	char	*helper;
	int 	enc;

	while (env_lnk)
	{
		if (ft_strncmp(env_lnk->key,"PATH", 5) == 0)
		{
			take = env_lnk->value;
			break ;
		}
		env_lnk = env_lnk->next;
	}
	if (!take)
		return (NULL);
	path = ft_split(take, ':');
	enc = 0;
	while (path[enc])
	{
		helper = path[enc];
		path[enc] = ft_strjoin(path[enc], "/");
		// free(helper);
		enc++;
	}
	return (path);
}

// this it will be changed to check also for the buildin
char	*pick(char**path, char*cmd)
{
	int		pass;
	char	*realpath;
	char	**cmdpath;

	pass = 0;
	if (ft_strrchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
		{
			cmdpath = ft_split(cmd, ' '); // will not do it
			return (cmdpath[0]);
		}
		return (NULL);
	}
	if (!path)
		return (perror("pipex"), exit(1), NULL);
	while (path[pass])
	{
		realpath = ft_strjoin(path[pass], cmd);
		if (access(realpath, X_OK) == 0)
			return (realpath);
		// free(realpath);
		pass++;
	}
	return (NULL);
}

void print_file_list(t_file *file)
{
    while (file)
    {
        printf("Infile: %s --->", file->infile);
        printf("Outfile: %s ---->", file->outfile);
        printf("Append: %d\n", file->append);
        file = file->next;
    }
}

void print_cmd_list(t_cmd *cmd)
{
    while (cmd)
    {
        if (cmd->file)
            print_file_list(cmd->file);
        else
            printf("No files attached.\n");

        cmd = cmd->next;
        printf("\n");
    }
}

void get_redirections(int *inf, int *outf,t_cmd* full)
{	
	t_file* files;

	files = full->file;
	*inf = -1;
	*outf = -1;
	while(files)
	{
		if(files->infile)
		{
			*inf = open(files->infile, O_RDONLY);
			if (*inf < 0)
			{
				perror("infile open failed");
				exit(EXIT_FAILURE);
			}
		}
		else if(files->outfile)
		{
			if(files->append)
				*outf =  open(files->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				*outf =  open(files->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (*outf < 0)
			{
				perror("outfile open failed");
				exit(EXIT_FAILURE);
			}
		}
		files = files->next;
	}
}

void	pipecheck(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}

void	forkfaild(pid_t pid, int*pipefd)
{
	if (pid == -1)
	{
		perror("pipex");
		close(pipefd[0]);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
}

void	handelprevpipe(int *pipefd, int *prev_pipe)
{
	close(pipefd[1]);
	close(*prev_pipe);
	*prev_pipe = pipefd[0];
}

void	execute_single_cmd(t_cmd *cmd, t_env *env, char **path)
{
	int	inf, outf;
	char **args = cmd->args;
	(void)env;
	get_redirections(&inf, &outf, cmd);

	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (inf != -1)
		{
			dup2(inf, STDIN_FILENO);
			close(inf);
		}
		if (outf != -1)
		{
			dup2(outf, STDOUT_FILENO);
			close(outf);
		}
		char *bin = pick(path, args[0]);
		if (!bin)
		{
			perror("command not found");
			exit(127);
		}
		execve(bin, args, NULL);
		perror("execve failed");
		exit(126);
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
	}
}

void exectution(t_cmd *full, t_env *env)
{
	int 	inf, outf;
	char    **path;
	pid_t	pid;
	int		pipefd[2];
	char**	cmd;
	int	perv_pipe = -1;

	path = takepaths(env);
	if (!path)
	{
		write(1, "there is no path\n", 17);
		exit(1);
	}

	if (full->next)
	{
		while(full)
		{
			pipecheck(pipefd);
			pid = fork();
			forkfaild(pid, pipefd);
			if (pid == 0)
			{
				// check if buildin
				get_redirections(&inf, &outf, full);

				if (inf != -1)
				{
					dup2(inf, STDIN_FILENO);
					close(inf);
				}
				else if (perv_pipe != -1)
					dup2(perv_pipe, STDIN_FILENO);

				if (outf != -1)
				{
					dup2(outf, STDOUT_FILENO);
					close(outf);
				}
				else if (full->next)
					dup2(pipefd[1], STDOUT_FILENO);

				close(pipefd[0]);
				close(pipefd[1]);

				cmd = full->args;
				char *pathh = pick(path, cmd[0]);
				if (!pathh)
				{
					perror("command not found");
					exit(127);
				}
				execve(pathh, cmd, NULL);
				perror("execve failed");
				exit(126);
			}
			else
			{
				handelprevpipe(pipefd, &perv_pipe);
			}
			full = full->next;
		}

		int status;
		while (wait(&status) > 0)
			;
	}
	else
		execute_single_cmd(full, env, path);
}
