/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:02:07 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/31 00:06:07 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	flag_helper(char **args)
{
	int	i;
	int	j;

	(1) && (i = 1, j = 0);
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
				return (0);
			else if (!args[i][j])
				return (0);
			else
				break ;
		}
		i++;
	}
	return (8);
}

int	check_flag(char**args, int i)
{
	int	j;

	if (!args[i])
		return (0);
	j = 0;
	if (args[i][j++] != '-')
		return (0);
	if (!args[i][j])
		return (0);
	while (args[i][j])
	{
		if (args[i][j] == 'n')
			j++;
		else
			return (0);
		if (!args[i][j])
			return (1);
	}
	return (1);
}

void	ft_echo(char **args, int exit_s)
{
	int	i;
	int	flag;
	int	j;

	(void)exit_s;
	(1) && (i = 1, flag = 0);
	flag = check_flag(args, i);
	if (flag == 1)
		i++;
	while (args[i])
	{
		j = 0;
		if (args[i][j])
			while (args[i][j])
				putchar(args[i][j++]);
		else
			putstr(args[i]);
		if (args[++i])
			putchar(' ');
	}
	exit_status(0, 1);
	if (flag == 1)
		return ;
	putstr("\n");
	exit_status(0, 1);
}
