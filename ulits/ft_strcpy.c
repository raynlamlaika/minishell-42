/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 01:11:45 by abouabba          #+#    #+#             */
/*   Updated: 2025/06/04 01:18:52 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcpy(char *dest, char *src)
{
	char	*original;

	if (!src || !dest)
		return (NULL);
	original = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (original);
}
