/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:58:40 by jroth             #+#    #+#             */
/*   Updated: 2022/03/31 16:06:54 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

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

char	str_cmp_n(char *str, char *cmp, int n)
{
	while (--n > 0 && *str && *cmp && *str == *cmp)
	{
		str++;
		cmp++;
	}
	return (*cmp - *str);
}

char	*join_paths(char *path, char *bin)
{
	int		i;
	int		j;
	char	*joined;

	joined = malloc(sizeof(char)
			* ((strlen_to_c(bin, 0) + strlen_to_c(path, 0)) + 2));
	i = 0;
	j = 0;
	while (path[j])
		joined[i++] = path[j++];
	joined[i++] = '/';
	j = 0;
	while (bin[j])
		joined[i++] = bin[j++];
	joined[i] = '\0';
	return (joined);
}

char	*find_path(char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (env[i] && str_cmp_n(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (path && strlen_to_c(path, ':') > -1)
	{
		dir = ft_strdupn(path, strlen_to_c(path, ':'));
		bin = join_paths(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += strlen_to_c(path, ':') + 1;
	}
	return (cmd);
}
