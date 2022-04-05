/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:41:08 by jroth             #+#    #+#             */
/*   Updated: 2022/04/05 20:37:54 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

void	skip_whitespace(char **str)
{
	while (whitespace(**str))
		(*str)++;
}

bool	whitespace(const char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (true);
	return (false);
}

void	myfree(void *mlc)
{
	if (mlc)
	{
		free(mlc);
		mlc = NULL;
	}
}
