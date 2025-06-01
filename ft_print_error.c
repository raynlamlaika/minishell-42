/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:36 by abouabba          #+#    #+#             */
/*   Updated: 2025/06/01 23:04:38 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_error(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write (2, &s[i], 1);
		i++;
	}
}

void	print_error_arg(char *line_1, char *arg, char *line_2)
{
	write (2, line_1, strlen(line_1));
	write (2, arg, strlen(arg));
	write (2, line_2, strlen(line_2));
}
