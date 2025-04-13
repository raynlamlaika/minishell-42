/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:45:49 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/04/13 11:13:46 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *handling_qoutes(char *word, char sepa)
{
	int i = 0;
	int count = 0;
	char *result;
	int j = 0;
	
	while (word[i])
	{
		if (word[i] != sepa)
			count++;
		i++;
	}
	result = malloc(count + 1);
	if (!result)
		return NULL;

	i = 0;

	while (word[i])
	{
		if (word[i] != sepa)
		{
			result[j] = word[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

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
	char	*take;
	char	*helper;
	int enc;

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
// char *openoutfile(t_file* files)
// {
// 	char*	outfile;
// 	// i think i  ned to open all files and after return the last file 

// 	return (outfile);

	

	
// }

void	exectution(t_cmd *full,t_env** env)
{
    (void)env;

    if (!full)
        exit (1);
    print_files_from_cmds(full);
	// init the args right here 
	char *infile = NULL;
	char *outfile = NULL;
	

	char	**paths;
	int		prev_pipe;
	int		outfile;

	// checkfor the build in
	// if it olny one commd it will wexec in the parent 
	
	prev_pipe = -1;
	paths = takepaths(env);
	// if (ft_strncmp("here_doc", av[1], 9) == 0)
	// 	return (heredoc(ac, av, paths), 0);

	printf("this is the path %s\n", paths[0]);
	// t_file *files  = full->file;
	// outfile = openoutfile(files);
	// checkinfile(av);
	// loop_childs(ac, &prev_pipe, av, paths);
	// last_child(prev_pipe, av[ac - 2], paths, outfile);
	// close(prev_pipe);
	// close(outfile);
	// clean_2(paths);
	// while (wait(NULL) != -1)
	// 	;
	// return (0);
}


// int main()
// {


//     printf("this is %s\n", handling_qoutes("$$\"$HOME'$HOME'$?\"\"\"", '\"'));
// }