/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:28:27 by jroth             #+#    #+#             */
/*   Updated: 2021/09/15 19:11:35 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *search, size_t n)
{
	size_t	i;

	if (!s && !search)
		return (NULL);
	if (ft_strlen(search) == 0)
		return ((char *)s);
	i = 0;
	while (*s && n > 0)
	{
		if (*s == *search)
		{
			i = 0;
			while (n > 0 && s[i] == search[i] && s[i])
			{
				i++;
				n--;
			}
			n += i;
			if (i == ft_strlen(search))
				return ((char *)s);
		}
		s++;
		n--;
	}
	return (NULL);
}
