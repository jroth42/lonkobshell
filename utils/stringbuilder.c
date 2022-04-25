/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:16:04 by jroth             #+#    #+#             */
/*   Updated: 2022/04/25 15:26:08 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

int	s_add_c(t_string *t_str, const char c)
{
	char	*tmp;
	char	*newstr;

	if (!c)
		return (1);
	newstr = ft_calloc(t_str->len + 2, sizeof(char));
	if (!newstr)
		return (2);
	s_copy(t_str, &newstr);
	newstr[(t_str->len)++] = c;
	tmp = t_str->str;
	t_str->str = newstr;
	free(tmp);
	return (0);
}

int	s_add_str(t_string *t_str, char *append)
{
	char	*tmp;
	int		i;
	char	*new;

	if (!append)
		return (2);
	new = ft_calloc(t_str->len + ((int) ft_strlen(append)) + 1, sizeof(char));
	if (!new)
		return (FAIL);
	s_copy(t_str, &new);
	i = 0;
	while (append[i])
	{
		new[t_str->len + i] = append[i];
		i++;
	}
	t_str->len += i;
	tmp = t_str->str;
	t_str->str = new;
	myfree(tmp);
	return (SUCCESS);
}

int	s_add_strn(t_string *t_str, char *append, int len)
{
	char	*tmp;
	int		i;
	char	*new;

	if (!append)
		return (FAIL);
	new = ft_calloc(t_str->len + len + 1, sizeof(char));
	if (!new)
		return (2);
	s_copy(t_str, &new);
	i = 0;
	while (append[i] && i < len)
	{
		new[t_str->len + i] = append[i];
		i++;
	}
	t_str->len += i;
	tmp = t_str->str;
	t_str->str = new;
	free(tmp);
	return (SUCCESS);
}

int	s_add_int(t_string *t_str, int n)
{
	char	*nbr;

	nbr = ft_itoa(n);
	if (!nbr)
		return (1);
	if (s_add_str(t_str, nbr))
	{
		free(nbr);
		nbr = 0;
		return (2);
	}
	free(nbr);
	nbr = 0;
	return (0);
}

char	*s_get_str(t_string *t_str)
{
	char	*res;
	int		i;

	if (!t_str)
		return (NULL);
	res = ft_calloc(t_str->len + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (t_str->str[i] && i < t_str->len)
	{
		res[i] = t_str->str[i];
		i++;
	}
	return (res);
}
