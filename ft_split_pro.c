/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pro.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:36:31 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/03/11 17:21:32 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include <stdlib.h>
#include <stdbool.h>
#include "minishell.h"



static size_t	count_word(char const *str)
{
	size_t	words;
	size_t	in_quotes;

	in_quotes = 0;
	words = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			1 && (in_quotes = !in_quotes) && (str++);
		if (!in_quotes && (*str == ' ' || *str == '\t'))
			str++;
		if (!in_quotes && (*str == '|' || *str == '<' \
		|| *str == '>' || *str == '&'))
		{
			1 && (words++) && (str++);
			if (*str == *str - 1)
				str++;
		}
		words++;
		while (*str && !(*str == ' ' || *str == '\t' || *str == '|' \
				|| *str == '<' || *str == '>' || *str == '&' || *str \
				== '"' || *str == '\''))
			str++;
	}
	return (words);
}

static size_t	length(char const *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '|' \
	&& str[i] != '<' && str[i] != '>' && str[i] != '&' && \
	str[i] != '"' && str[i] != '\'')
		i++;
	return (i);
}

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!src || !dest)
		return (NULL);
	while (i < n && src[i])
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

static char	**parse_s_c(char const *s, char **p, size_t *index, bool *in_quotes)
{
	if (*s == '"' || *s == '\'')
	{
		*in_quotes = !(*in_quotes);
		return (p);
	}
	if (!(*in_quotes) && (*s == ' ' || *s == '\t'))
		return (p);
	if (!(*in_quotes) && (*s == '|' || *s == '<' || *s == '>' || *s == '&'))
	{
		p[*index] = (char *)malloc(2 * sizeof(char));
		if (!p[*index])
			return (NULL);
		p[*index][0] = *s;
		p[*index][1] = '\0';
		(*index)++;
	}
	return (p);
}

static char	**parse_words(char const *s, char **p, size_t *index)
{
	size_t	word_len;

	word_len = length(s);
	p[*index] = (char *)malloc((word_len + 1) * sizeof(char));
	if (!p[*index])
		return (NULL);
	ft_strncpy(p[*index], s, word_len);
	p[*index][word_len] = '\0';
	(*index)++;
	return (p);
}

static char	**handel_s_ch(char const **s, \
char **p, size_t *index, bool *in_quts)
{
	if (**s == '"' || **s == '\'' || \
	(!*in_quts && (**s == ' ' || **s == '\t')))
		(*s)++;
	else if (!*in_quts && (**s == '|' || \
	**s == '<' || **s == '>' || **s == '&'))
	{
		(*s)++;
		if ((**s == '>' && *(*s - 1) == '>') \
		|| (**s == '&' && *(*s - 1) == '&'))
		{
			(*s)++;
		}
	}
	else
	{
		p = parse_words(*s, p, index);
		if (!p)
			return (NULL);
		*s += length(*s);
	}
	return (p);
}

static char	**intotowdarray(char const *s, char **p)
{
	size_t	index;
	bool	in_quts;

	index = 0;
	in_quts = false;
	while (*s)
	{
		p = parse_s_c(s, p, &index, &in_quts);
		if (!p)
			return (NULL);
		p = handel_s_ch(&s, p, &index, &in_quts);
		if (!p)
			return (NULL);
	}
	return (p);
}

char	**ft_split(char const *s)
{
	size_t	words;
	char	**p;

	if (!s)
		return (NULL);
	words = count_word(s);
	p = (char **)malloc(sizeof(char *) * (words + 1));
	if (!p)
		return (NULL);
	p = intotowdarray(s, p);
	if (!p)
		return (NULL);
	p[words] = NULL;
	return (p);
}
int main(int ac, char**av)
{

	char *r ="<\"c\"\"a\"\"t\" | ls > derer ";
	char**u= ft_split(r);
	for (int i =0;u[i];i++)
		printf("this is :%s\n",u[i]);
}