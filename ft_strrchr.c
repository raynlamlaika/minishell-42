/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:17:00 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/04/14 16:18:58 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strrchr(char *str, int c)
{
	size_t	i;
	char	*ptr;
	char	a;

	a = (char)c;
	ptr = (char *)str;
	i = ft_strlen(str);
	while (i > 0 && ptr[i] != a)
	{
		i--;
	}
	if (ptr[i] == a)
		return ((char *)&ptr[i]);
	else
		return (NULL);
}
