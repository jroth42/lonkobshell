/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:41:08 by jroth             #+#    #+#             */
/*   Updated: 2022/04/24 20:21:50 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

void	skip_white_space(char **str)
{
	while (white_space(**str))
		(*str)++;
}

bool	white_space(const char c)
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

int	get_arr_size(char **arr)
{
	int	res;

	res = 0;
	while (arr[res])
		res++;
	return (res);
}

int	error_msg(char *error_msg, int r_value)
{
	ft_putstr_fd("lonkob: ", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putchar_fd('\n', 2);
	return (r_value);
}
