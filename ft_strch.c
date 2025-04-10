/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:17:26 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/04/09 14:17:39 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*ptr;
	char	x;

	ptr = (char *)str;
	x = (char)c;
	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == x)
			return ((char *)(ptr + i));
		i++;
	}
	if (x == '\0')
		return ((char *)(ptr + i));
	return (NULL);
}
