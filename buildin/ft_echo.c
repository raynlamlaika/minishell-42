/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:02:07 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/04/12 18:22:19 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void ft_echo(char **args)
{
    int i;
    int j = 0;
    char p;

    i = 0;
    // p = '\n';
    if (!args)
        ;
    // check the first param
    if (ft_strncmp(args[i] , "-n", 3) == 0)
        p = '\n';
    i++;
    while (args[i])
    {
        printf("%s", args[i]);
        j = i + 1;
        if (args[j])
            printf(" ");
        i++;
    }
}


int main()
{
    int i = 0;
    char **p = malloc(sizeof(char *) * (3 + 1)); 


    for (int i = 0; i < 3;i++)
    {
        p[i] = malloc(9);
        p[i] = "helooooo";
    }
    ft_echo(p);

    return (0);
}