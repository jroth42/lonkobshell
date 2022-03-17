/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:31:17 by jroth             #+#    #+#             */
/*   Updated: 2021/11/10 13:23:37 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// finds rest of string starting from i
size_t	sublen(size_t i, char *str)
{
	while (str[i] != '\0')
		i++;
	return (i);
}

// frees string and 'NULL's it
void	ifree(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

// searches for a character and returns length to it, -1 if not found
int	isearchlen(const char *str, char c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	if (c == '\0')
	{
		while (str[i] != '\0')
			i++;
		return (i);
	}
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

// reserves memory for a string and sets NULLbytes
void	*icalloc(size_t count, size_t size)
{
	size_t		len;
	char		*ptr;

	len = size * count;
	ptr = malloc(len);
	if (ptr == NULL)
		return (NULL);
	while (len > 0)
	{
		ptr[len - 1] = 0;
		len--;
	}
	return ((void *)ptr);
}

// cuts out substring from starting point to given size
char	*isubstring(char *str, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ret;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (i >= start && j < len)
		{
			ret[j] = str[i];
			j++;
		}
		i++;
	}
	ret[j] = '\0';
	return (ret);
}
