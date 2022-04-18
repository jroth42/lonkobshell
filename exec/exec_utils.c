/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:58:40 by jroth             #+#    #+#             */
/*   Updated: 2022/04/18 22:08:40 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

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
		myfree(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		myfree(bin);
		path += strlen_to_c(path, ':') + 1;
	}
	return (cmd);
}

int	file_error(char *name_b, char *msg, char *name_a)
{
	if (name_b)
		ft_putstr_fd(name_b, 2);
	if (msg)
	{
		if (name_b)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
	}
	if (name_a)
	{
		if (msg)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(name_a, 2);
	}
	ft_putchar_fd('\n', 2);
	return (EXIT_FAILURE);
}

int	open_file(char *file, int mode, int rights)
{
	int	fd;

	fd = open(file, mode, rights);
	if (fd < 0 || access(file, W_OK) < 0)
	{
		file_error("minishell", "errno", file);
		return (-1);
	}
	return (fd);
}
