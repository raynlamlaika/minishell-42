/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:02:07 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/26 14:27:07 by rlamlaik         ###   ########.fr       */
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

int	putnbr(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		i += putstr("-2147483648");
		return (i);
	}
	else if (n < 0)
	{
		n = -n;
		i += write(1, "-", 1);
		i += putnbr(n);
	}
	else if (n > 9)
	{
		i += putnbr(n / 10);
		i += putnbr(n % 10);
	}
	else if (n <= 9 && n >= 0)
		i += putchar(n + '0');
	return (i);
}
void ft_echo(char **args, int exit_s)
{
	int i = 0;
	int flag;
	int u= 0;
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
	while (ft_strncmp(args[i] , "-n", 2) == 0 && u == 0)
	{
		j = 2;
		if (args[i][j])
		{
			while (args[i][j])
			{
				if (args[i][j] != 'n')
				{
					i = 0;
					flag = 0;
					u = 1;
					break;
				}
				j++;
			}
		}
		i++;
		flag = 5;
		if (u != 0)
			flag =0 ;
	}
	while (args[i])
	{
		j = 0;
		if (args[i][j])
		{
			while(args[i][j])
			{
				if (args[i][j]  == '$')
				{
					if (args[i][++j] == '?')
						putnbr(exit_s);
					else
						j--;
				}
				else 
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
	if (flag == 0)
		putstr( "\n");
	exit_s = 0;
}

