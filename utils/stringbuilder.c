/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:16:04 by jroth             #+#    #+#             */
/*   Updated: 2022/04/21 17:07:18 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

t_string *s_create(void)
{
	t_string	*new;
	
	new = calloc(1, sizeof(t_string));
	if (!new)
		return (NULL);
	new->str = ft_calloc(1, sizeof(char));
	new->len = 0;
	return (new);
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
	s_copy(t_str , &new);
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

int	s_destroy(t_string *t_str)
{
	free(t_str->str);
	t_str->str = NULL;
	t_str->len = 0;
	free(t_str);
	t_str = NULL;
	return (0);
}

// void	test_string(void)
// {
// 	t_string *t_str;

// 	t_str = s_create();
// 	s_add_str(t_str, "hey ich bin der erste!\n");
// 	s_add_str(t_str, "... und ich der zweite\n");
// 	s_add_c(t_str, 'F');
// 	s_add_strn(t_str, "\n jetzt hoerts aber auf", 7);
// 	s_add_int(t_str, 420);
// 	s_reset(t_str);
// 	s_destroy(t_str);
// 	printf("%d ... %s", t_str->len, t_str->str);
// }