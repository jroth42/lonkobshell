/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:32:14 by jroth             #+#    #+#             */
/*   Updated: 2021/09/10 14:16:07 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(const char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	neg;
	int	bool;

	while (ft_isspace(*str) == 1)
		str++;
	neg = 1;
	if (*str == '-')
		neg = -1;
	if (*str == '-' || *str == '+')
		str++;
	res = 0;
	bool = 1;
	while (*str && bool)
	{
		if (ft_isdigit(*str) == 1)
			res = res * 10 + *str - 48;
		else
			bool = 0;
		str++;
	}
	return (res * neg);
}
