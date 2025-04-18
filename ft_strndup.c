/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:09:39 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/04/13 16:43:12 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*ft_strndup(char *s1, int n)
{
	int		i;
	char	*s2;

	s2 = malloc((1 + n) * (sizeof(char)));
	if (!s2)
		return (NULL);
	i = 0;
	while (i < n && s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
