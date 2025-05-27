/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:02:07 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/27 10:24:25 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	putstr(char *string)
{
	int	i;

	i = 0;
	if (!string)
		i += write(1, "(null)", 6);
	else
	{
		while (*string)
		{
			i += putchar(*string);
			string++;
		}
	}
	return (i);
}

int	flag_helper(char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i][j])
	{
		j = 0;
		if (args[i][j] == '-')
			j++;
		else
			break ;
		while (args[i][j])
		{
			if (args[i][j] == 'n')
				j++;
			else if (args[i][j] == ' ')
				return(0);
			else if (!args[i][j])
				return (0);
			else
				break ;
		}
		i++;		
	}
	return (8);
}

void ft_echo(char **args, int exit_s)
{
	int i = 0;
	int flag;
	(void)exit_s;
	int j;
	
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
	// if (args[i][0] == '-')
	// 	flag = flag_helper(args);
	// printf("this is sthe flaaaaaaaaaag %d\n", flag);
	while (args[i])
	{
		j = 0;
		if (args[i][j])
		{
			while(args[i][j])
			{
				putchar(args[i][j]);
				j++;
			}
		}
		else
			putstr(args[i]);            
		i++;
		if (args[i])
			putchar(' ');
	}
	putstr( "\n");
	exit_s = 0;
}

