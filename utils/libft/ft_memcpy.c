/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:28:14 by jroth             #+#    #+#             */
/*   Updated: 2021/09/15 20:58:04 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*ptr_s;
	char		*ptr_d;

	ptr_s = src;
	ptr_d = dst;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n > 0)
	{
		*ptr_d = *ptr_s;
		ptr_d++;
		ptr_s++;
		n--;
	}
	return (dst);
}
