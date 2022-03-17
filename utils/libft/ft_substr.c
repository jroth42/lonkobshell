/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:29:43 by jroth             #+#    #+#             */
/*   Updated: 2021/09/15 19:36:45 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*d;

	if (!s)
		return (NULL);
	if (start > ((size_t) ft_strlen(s)))
		return (ft_calloc(1, 1));
	d = malloc(sizeof(char) * (len + 1));
	if (!d)
		return (NULL);
	j = 0;
	i = 0;
	while (s[i] && j < len)
	{
		if (i >= start)
			d[j++] = s[i];
		i++;
	}
	d[j] = '\0';
	return (d);
}
