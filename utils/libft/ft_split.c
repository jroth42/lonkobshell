/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 12:22:39 by jroth             #+#    #+#             */
/*   Updated: 2021/09/14 20:37:54 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(const char *s, char c)
{
	int	i;
	int	delimit;

	i = 0;
	delimit = 0;
	while (*s)
	{
		if (delimit == 0 && *s != c)
		{
			delimit = 1;
			i++;
		}
		else if (*s == c)
			delimit = 0;
		s++;
	}
	return (i);
}

static char	*ft_write(const char *s, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * ((end - start) + 1));
	if (!word)
		return ((char *)(NULL));
	i = 0;
	while ((start + i) < end)
	{
		word[i] = s[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;
	size_t	j;
	int		start;

	if (!s)
		return ((char **) NULL);
	split = ft_calloc(sizeof(char *) * (ft_count(s, c) + 1), 1);
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	start = -1;
	while (++i <= ft_strlen(s) + 1)
	{
		if (s[i - 1] != c && start < 0)
			start = i - 1;
		else if (start >= 0 && (s[i - 1] == c || (i - 1) == ft_strlen(s)))
		{
			split[j++] = ft_write(s, start, i - 1);
			start = -1;
		}
	}
	return (split);
}
