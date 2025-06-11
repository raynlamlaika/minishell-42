/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:43:48 by abouabba          #+#    #+#             */
/*   Updated: 2025/06/11 00:25:43 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit((unsigned char)str[i]))
			return (0);
		i++;
	}
	return (1);
}

long long	ft_str_to_ll(const char *str, int *overflow)
{
	int				sign;
	unsigned long	result;
	int				i;

	*overflow = 0;
	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i])
	{
		if (result > (unsigned long)(LLONG_MAX - (str[i] - '0')) / 10)
			return (*overflow = 1, 0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (sign == -1 && result > (unsigned long)LLONG_MAX + 1)
		*overflow = 1;
	if (sign == 1 && result > (unsigned long)LLONG_MAX)
		*overflow = 1;
	return ((long long)(result * sign));
}

void	exit_with_error(char *args)
{
	print_error_arg("minishell: exit: ", args, "\
 : numeric argument required\n");
	exit_status(1, 2);
	ft_malloc(0, 0);
	exit(2);
}

void	ft_exit(char **args, int exit_status, t_cmd *cmd)
{
	long long	value;
	int			overflow;

	if (cmd->exit_flag == 42)
		printf("exit\n");
	if (!args[1])
	{
		ft_malloc(0, 0);
		exit(exit_status);
	}
	if (!is_numeric(args[1]))
		exit_with_error(args[1]);
	value = ft_str_to_ll(args[1], &overflow);
	if (overflow)
		exit_with_error(args[1]);
	if (args[2])
	{
		printf_error("minishell: exit: too many arguments\n");
		return ;
	}
	ft_malloc(0, 0);
	exit((unsigned char)value);
}
