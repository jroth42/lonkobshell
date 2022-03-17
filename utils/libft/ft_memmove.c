/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:28:15 by jroth             #+#    #+#             */
/*   Updated: 2021/09/09 18:25:09 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	const char	*ptr_s;
	char		*ptr_d;

	if (dst > src)
	{
		ptr_s = src + (n - 1);
		ptr_d = dst + (n - 1);
	}
	else
		return (ft_memcpy(dst, (void *)src, n));
	while (n > 0)
	{
		*ptr_d = *ptr_s;
		ptr_d--;
		ptr_s--;
		n--;
	}
	return (dst);
}
