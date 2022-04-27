/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder_create.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:26:32 by jroth             #+#    #+#             */
/*   Updated: 2022/04/27 18:10:34 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

int	s_destroy(t_string *t_str)
{
	free(t_str->str);
	t_str->str = NULL;
	t_str->len = 0;
	free(t_str);
	t_str = NULL;
	return (0);
}

int	s_reset(t_string *str)
{
	myfree(str->str);
	str->str = ft_calloc(1, 1);
	if (!str->str)
	{
		myfree(str);
		return (FAIL);
	}
	str->len = 0;
	return (SUCCESS);
}

void	s_copy(t_string *old, char **new)
{
	int		i;

	i = -1;
	if (old && old->str && new)
	{
		while (old->str[++i])
			(*new)[i] = old->str[i];
	}		
}

t_string	*s_create(void)
{
	t_string	*new;

	new = ft_calloc(1, sizeof(t_string));
	if (!new)
		return (NULL);
	new->str = ft_calloc(1, sizeof(char));
	new->len = 0;
	return (new);
}
