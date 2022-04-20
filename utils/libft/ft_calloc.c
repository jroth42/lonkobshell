/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:33:26 by jroth             #+#    #+#             */
/*   Updated: 2022/04/20 19:17:04 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
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
