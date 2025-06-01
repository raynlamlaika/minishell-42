/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 08:13:07 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/28 10:51:04 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	putstr(char *string)
{
	int	i;

	i = 0;
	if (!string)
		return (0);
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
