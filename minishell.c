/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:29:38 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/03/11 09:45:18 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>

int parssing(char *line)
{
    char**args;
    
    args = ft_split(line);
    

    
}


char* get_line(int ac, char**av, char**env)
{
    char *input;

    input = readline("Hell SHELLL|>");
    if (!input)
        return (printf("error in the read line function\n"), free(input), exit(1),NULL);
    return (input);
}


int main(int ac, char**av, char**env)
{
    char *line;

    while (1)
    {
        line = get_line(ac, av, env);
        //exectute
        printf("thisis the line%s\n",line);
        free(line);
        if (!line)
            break;
    }
    free(line);
    return (0);
}



