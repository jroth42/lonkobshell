/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:32:14 by jroth             #+#    #+#             */
/*   Updated: 2022/03/18 16:13:03 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	neg;

	while (*str == ' ' || *str == '\n' || *str == '\t'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	neg = 1;
	if (*str == '-')
		neg = -1;
	if (*str == '-' || *str == '+')
		str++;
	res = 0;
	while (*str)
	{
		if (*str >= 48 && *str <= 57)
			res = res * 10 + *str - 48;
		else
			break ;
		str++;
	}
	return (res * neg);
}
