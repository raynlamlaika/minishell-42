/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:02:07 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/19 10:29:39 by rlamlaik         ###   ########.fr       */
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
        return ;
    while (ft_strncmp(args[i] , "-n", 2) == 0)
    {
        i++;
        flag = 5;
    }
    while (args[i])
    {
        int j = 0;
        if (args[i][j])
        {
            while(args[i][j])
            {
                if (args[i][j]  == '$')
                {
                    if (args[i][++j] == '?')
                        printf("%d", exit_s);
                    else
                        j--;
                }
                else 
                    printf("%c", args[i][j]);
                j++;
            }
            // printf(" ");
        }
        else
        {
            printf("%s", args[i]);            
        }
        i++;
        if (args[i])
            printf(" ");
    }
    if (flag == 0)
        printf("\n");
    exit_s = 0;
}
