/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:36 by abouabba          #+#    #+#             */
/*   Updated: 2025/06/19 05:54:20 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

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
	char	*tmp;
	char	*msg;

	tmp = ft_strjoin(line_1, arg);
	if (!tmp)
		return ;
	msg = ft_strjoin(tmp, line_2);
	if (!msg)
		return ;
	write(2, msg, ft_strlen(msg));
}
