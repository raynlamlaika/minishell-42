/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:17:14 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/10 20:09:15 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	ft_strlen(char *s1)
{
	int	i;

	i = 0;
	if (!s1)
		return(0);
	while (s1[i])
		i++;
	return (i);
}

char	*ft_strdup(char*source)
{
	size_t	o;
	char	*sp;

	o = 0;
	sp = (char *) ft_malloc((ft_strlen(source) + 1) * sizeof(char), 1);
	if (!sp)
		return (NULL);
	while (source[o])
	{
		sp[o] = source[o];
		o++;
	}
	sp[o] = '\0';
	return (sp);
}
