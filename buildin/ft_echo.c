/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:02:07 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/04/13 17:24:23 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void ft_echo(char **args)
{
    int i;
    int j = 0;
    char p;
    int flag;

    i = 0;
    // p = '\n';
    flag = 0;
    if (!args)
        ;
    // check the first param
    printf("caek charekc %s %d\n",args[i] ,ft_strncmp(args[i], "echo", 4));
    if (ft_strncmp(args[i] , "echo", 4) == 0)
        i++;
    else
        exit(1);
    i++;
    if (ft_strncmp(args[i] , "-n", 3) == 0)
        flag = 5;
    i++;
    while (args[i])
    {
        printf("%s", args[i]);
        j = i + 1;
        if (args[j])
            printf(" ");
        i++;
    }
    if (flag == 0)
        printf("\n");
}
