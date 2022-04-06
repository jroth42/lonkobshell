/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:58:40 by jroth             #+#    #+#             */
/*   Updated: 2022/04/06 16:50:51 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

void	check_redirects(t_exec *exec, t_cmd *cmd)
{
	if (cmd->re_in)
		exec->file_fd = open_file(cmd->re_in, INFILE, cmd->re_type);
	if (cmd->re_out)
		exec->file_fd = open_file(cmd->re_out, OUTFILE, cmd->re_type);
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
		myfree(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		myfree(bin);
		path += strlen_to_c(path, ':') + 1;
	}
	return (cmd);
}

int	open_file(char *file, int mode, int type)
{
	if (mode == INFILE)
	{
		if (access(file, F_OK) != 0)
		{
			write(STDERR_FILENO, "Couldn't find file: ", 21);
			write(STDERR_FILENO, file, strlen_to_c(file, 0));
			write(STDERR_FILENO, "\n", 1);
			return (STDIN_FILENO);
		}
		return (open(file, O_RDONLY));
	}
	else if (type == LESSLESS || type == LESS)
		return (open(file, O_CREAT | O_WRONLY | O_APPEND));
	else if (type == GREAT)
		return (open(file, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
	else if (type == GREATGREAT)
		return (open(file, O_CREAT | O_WRONLY | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
	return (0);
}
