/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:48:23 by jroth             #+#    #+#             */
/*   Updated: 2022/03/19 18:09:10 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdupn(const char *s1, int n)
{
	char		*s2;
	int			i;

	s2 = malloc(sizeof(char) * n + 1);
	if (!s2)
		return ((char *) NULL);
	i = 0;
	while (i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
