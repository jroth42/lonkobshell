/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:37:55 by jroth             #+#    #+#             */
/*   Updated: 2022/04/26 16:39:30 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	len = (int) ft_strlen(s1) + (int) ft_strlen(s2);
	s3 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s3)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while ((int) j < (int) ft_strlen(s2))
	{
		s3[i++] = s2[j++];
	}
	s3[i] = '\0';
	return (s3);
}
