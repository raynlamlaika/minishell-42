/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:47:46 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/04/12 16:03:39 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check(char const *s1, char const *s2)
{
	char	*p;

	if (!s1)
	{
		p = ft_strdup(s2);
		return (p);
	}
	if (!s2)
	{
		p = ft_strdup(s1);
		return (p);
	}
	else
		return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*ptr;

	if (!s1 && !s2)
		return (0);
	if ((!s1 && s2) || (!s2 && s1))
		return (check(s1, s2));
	i = ft_strlen(s1)+ ft_strlen(s2);
	ptr = (char *) malloc((i + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		ptr[i] = *s2;
		i++;
		s2++;
	}
	ptr[i] = '\0';
	return (ptr);
}
