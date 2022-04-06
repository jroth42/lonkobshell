/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:41:08 by jroth             #+#    #+#             */
/*   Updated: 2022/04/06 16:41:58 by jroth            ###   ########.fr       */
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

int	strlen_to_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}
