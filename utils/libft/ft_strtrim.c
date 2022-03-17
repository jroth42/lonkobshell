/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:58:22 by jroth             #+#    #+#             */
/*   Updated: 2021/09/15 17:39:02 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischaracter(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	i;
	size_t	j;
	size_t	size;

	if (!s1)
		return (NULL);
	size = ft_strlen(s1);
	j = size - 1;
	i = 0;
	while (ft_ischaracter(s1[i], set) == 1 && s1[i])
		i++;
	while (ft_ischaracter(s1[j], set) == 1 && j > i)
		j--;
	size = j - i + 1;
	trim = (char *)malloc(sizeof(char) * (size + 1));
	if (!trim)
		return (NULL);
	j = 0;
	while (j < size)
		trim[j++] = s1[i++];
	trim[j] = '\0';
	return (trim);
}
