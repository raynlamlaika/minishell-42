/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:47:46 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/03 14:53:53 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *r, char *w)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!r && !w)
		return (NULL);
	if (!r)
		return (ft_strdup(w));
	if (!w)
		return (ft_strdup(r));
	str = (char *)ft_malloc(sizeof(char) * \
	((ft_strlen(r) + ft_strlen(w)) + 1), 1);
	if (!str)
		return (NULL);
	while (r[i])
	{
		str[i] = r[i];
		i++;
	}
	while (w[j])
		str[i++] = w[j++];
	str[i] = '\0';
	return (str);
}
