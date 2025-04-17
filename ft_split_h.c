/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:57:42 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/04/13 17:27:33 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

static size_t	count_word(char const *str, char c)
{
	size_t	i;
	size_t	o;

	o = 0;
	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if ((*str != c) && o == 0)
		{
			o = 1;
			i++;
		}
		else if (*str == c)
			o = 0;
		str++;
	}
	return (i);
}

static size_t	lenght(char const *str, char c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (*str && *str != c)
	{
		i++;
		str++;
	}
	return (i);
}

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!src || !dest)
		return (0);
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

static char	**intotowdarray(char const*s, char c, char**p, size_t*index)
{
	size_t	words;

	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != c && *s != '\0')
		{
			words = lenght(s, c);
			p[*index] = (char *) malloc(sizeof(char) * (words + 1));
			if (!p)
			{
				while ((*index) > 0)
					free(p[(*index)--]);
				free (p);
				return (0);
			}
			ft_strncpy(p[*index], s, words);
			p[*index][words] = '\0';
			(*index)++;
			s += words;
		}
	}
	return (p);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**p;
	size_t	index;

	if (!s)
		return (NULL);
	words = count_word(s, c);
	p = (char **) malloc(sizeof(char *) * (1 + words));
	if (!p)
		return (NULL);
	index = 0;
	p = intotowdarray(s, c, p, &index);
	if (!p)
		return (NULL);
	p[index] = NULL;
	return (p);
}
