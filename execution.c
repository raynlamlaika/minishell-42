/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:45:49 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/04/17 16:59:54 by rlamlaik         ###   ########.fr       */
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
		free(helper);
		enc++;
	}
	return (path);
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
		free(realpath);
		pass++;
	}
	return (NULL);
}


int	first_command(int infile, char **paths, int *pipfd, char**arg)
{
	char	*path;

	if (infile < 0)
		exit(1);
	if (dup2(infile, STDIN_FILENO) == -1)
		return (perror("pipex"), exit(1), 0);
	close(infile);
	if (dup2(pipfd[1], STDOUT_FILENO) == -1)
		return (perror("pipex"), close(pipfd[1]), exit(1), 0);
	close(pipfd[1]);
	close(pipfd[0]);
	path = pick(paths, arg[0]);
	if (!path)
		return (perror("pipex"), close(infile), exit(1), 0);
	execve(path, arg, NULL);
	exit(1);
	return (1);
}

int	executing(int prev_pipe, char**cmd, char**paths, int outfile)
{
	char	*path;

	if (dup2(prev_pipe, STDIN_FILENO) == -1)
		return (perror("pipex"), 0);
	close(prev_pipe);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		return (perror("pipex"), close(prev_pipe), 0);
	close(outfile);
	path = pick(paths, cmd[0]);
	if (!path)
		return (perror("pipex"), close(prev_pipe), close(outfile), exit(1), 0);
	if (execve(path, cmd, NULL) == -1)
	{
		perror("pipex");
		exit(1);
	}
	return (0);
}

void	handelprevpipe(int *pipefd, int *prev_pipe)
{
	close(pipefd[1]);
	close(*prev_pipe);
	*prev_pipe = pipefd[0];
}

t_cmd*	loop_childs(int *prev_pipe, char**paths, t_cmd *args, int inf)
{
	// t_cmd	*last;
	pid_t	pid;
	int		pipfd[2];
	t_cmd	*curr;
	int i = 0;
	
	curr = args;

	while (curr->next)
	{

		pipecheck(pipfd);
		printf("this is the prev pip %d and outf  %d\n", inf, prev_pipe[0]);
		pid = fork();
		forkfaild(pid, pipfd);
		if (pid == 0)
		{
			if ( i == 0) // take the first cmd
				first_command(inf, paths, pipfd, args->args);
			if (i > 0)// others
			{
				close(pipfd[0]);
				exit(1);
				executing(*prev_pipe, args->args, paths, pipfd[1]);
			}
		}
		else
			handelprevpipe(pipfd, prev_pipe);
		i++;
		// printf("this is the args %s\n", curr->args[0]);
		curr = curr->next;
	}
	return (curr);
}

int	last_child(int prvpipe, char**cmd, char**paths, int outf)
{
	char	*path;

	printf("this is the prev pip %d and outf%d\n", prvpipe, outf);
	if (fork() == 0)
	{
		if (dup2(prvpipe, STDIN_FILENO) == -1)
			return (perror("pipex"), 0);
		close(prvpipe);
		if (dup2(outf, STDOUT_FILENO) == -1)
			return (perror("pipex"), close(prvpipe), 0);
		close(outf);
		path = pick(paths, cmd[0]);
		if (!path)
			return (perror("pipex"), close(prvpipe), close(outf), exit(1), 0);
		if (execve(path, cmd, NULL) == -1)
		{
			perror("pipex");
			exit(1);
		}
	}
	return (0);
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

int open_outf(t_file* current)
{
	int fd;

	fd = 0;
	while (current)
	{
		if (!current->outfile)
		{
			// printf("WE WILL USE THE STDIN/OUT this is the fd %d\n", fd);
			return -5;
		}
		else if (current->append)
			fd = open(current->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(current->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		printf("OUUUUUUUTening input file: %s number %d\n", current->outfile, fd);
		if (fd == -1)
		{
			perror("Failed to open file");
			return (0); // or exit status will be handeled here
		}
		if (current->next)
			close(fd);
		current = current->next;
	}
	//we  will open the last file 
	return (fd);
}

int open_infile(t_file *current)
{
	int fd = 0;

	while (current)
	{
		if (!current->infile)
		{
			// printf("No infile specified, using STDIN\n");
			// current = current->next;
			return (-5);
		}
		fd = open(current->infile, O_RDONLY);
		printf("Opening input file: %s number %d\n", current->infile, fd);
		if (fd == -1)
		{
			perror("Failed to open input file");
			return (0); // You can handle this however you want
		}
		if (current->next)
			close(fd);
		current = current->next;
	}
	return (fd); // return the last valid input fd to dup2 to STDIN
}


void exectution(t_cmd *full, t_env *env)
{
	// int     inf, outf;
	// char    **path;
	// int     i = 0;

	(void) full;
	(void)env;
	// path = takepaths(env);
	// if (!path)
	// 	return ; // or handle error

	// while (full->next) // process all commands except the last
	// {
	// 	hedel_red(full);
	// 	inf = open_infile(full);
	// 	outf = open_outf(full);

	// 	if (inf != -1)
	// 		dup2(inf, STDIN_FILENO);
	// 	if (outf != -1)
	// 		dup2(outf, STDOUT_FILENO);

	// 	if (i == 0)
	// 		first_command(full, path, env); // first command logic
	// 	else
	// 		executing(full, path, env);     // middle commands

	// 	i++;
	// 	full = full->next;
	// }

	// // last command
	// last_command(full, path, env);
}

