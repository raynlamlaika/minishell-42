/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:02:07 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/09 21:01:16 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void ft_echo(char **args, int exit_s)
{
    int i = 0;
    int flag;
    
    flag =0;
    
    if (!args)
    {
        write(1,"\n",1);
        exit(127);
    }
    if (ft_strcmp(args[i] , "echo") == 0)
    i++;
    else
    if (ft_strncmp(args[i] , "-n", 2) == 0)
    flag = 5;
    while (args[i])
    {
        int j = 0;
        if (ft_strncmp(args[i] , "$?", 2) == 0)
        {
            // hANDEL "$?H44H4HH4"
            printf("%d", exit_s);
            if (args[i][j + 2])
            {
                j = 2;
                while(args[i][j])
                {
                    printf("%c", args[i][j]);
                    j++;
                }
                printf(" ");
            }
        }
        else
            printf("%s ", args[i]);
        i++;
    }
    if (flag == 0)
        printf("\n");
}
