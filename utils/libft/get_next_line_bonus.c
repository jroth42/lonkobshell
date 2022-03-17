/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:31:36 by jroth             #+#    #+#             */
/*   Updated: 2021/11/10 15:01:09 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// return new string containing given strings
char	*ijoin(char *nl, char *bf)
{
	size_t	len;
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!nl)
		nl = isubstring("", 0, 0);
	len = sublen(i, nl) + sublen(j, bf);
	ret = icalloc((len + 1), sizeof(char));
	if (ret == NULL)
		return (NULL);
	while (nl[i] != '\0')
	{
		ret[i] = nl[i];
		i++;
	}
	while (i < len)
		ret[i++] = bf[j++];
	if (nl != NULL)
		ifree(&nl);
	return (ret);
}

//is used if buffer contains multiple \n or only \n
char	*bigbuff(char	**newline)
{
	char	*tmp;
	char	*ret;
	size_t	nl;

	if (isearchlen(*newline, '\n') == 0)
		ret = isubstring(*newline, 0, 1);
	else
		ret = isubstring(*newline, 0, isearchlen(*newline, '\n') + 1);
	nl = (isearchlen(*newline, '\n') + 1);
	tmp = isubstring(*newline, nl, sublen(nl, *newline));
	ifree(newline);
	*newline = tmp;
	return (ret);
}

//returns newline with trimmed version of (conjoined) buffer(s)
char	*ireturn(char	**newline, size_t rd)
{
	char	*ret;

	if (*newline)
	{
		if (rd <= 0 && **newline == '\0')
		{
			ifree(&(*newline));
			return (NULL);
		}
	}
	if (isearchlen(*newline, '\n') == -1)
	{
		ret = isubstring(*newline, 0, isearchlen(*newline, '\0'));
		ifree(&(*newline));
	}
	else
		ret = bigbuff(newline);
	return (ret);
}

//gets a line from the fd at a time
char	*get_next_line(int fd)
{
	char			*newline;
	static char		*buff[10240];
	int				rd;

	if (fd < 0 || fd > 10240 || BUFFER_SIZE < 1)
		return (NULL);
	newline = NULL;
	rd = 0;
	while (isearchlen(buff[fd], '\n') < 0)
	{
		newline = icalloc(BUFFER_SIZE + 1, sizeof(char));
		rd = read(fd, newline, BUFFER_SIZE);
		if (!newline || rd == -1)
		{
			ifree(&newline);
			return (NULL);
		}
		if (rd < 1)
			break ;
		buff[fd] = ijoin(buff[fd], newline);
		ifree(&newline);
	}
	ifree(&newline);
	return (ireturn(&buff[fd], rd));
}
