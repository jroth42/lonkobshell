/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:03:58 by jroth             #+#    #+#             */
/*   Updated: 2022/03/31 21:06:45 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"


int	open_file(char *file, int mode, int bonus)
{
	if (mode == INFILE)
	{
		if (access(file, F_OK))
		{
			write(STDERR, "Couldn't find file: ", 21);
			write(STDERR, file, strlen_to_c(file, 0));
			write(STDERR, "\n", 1);
			return (STDIN);
		}
		return (open(file, O_RDONLY));
	}
	else if (bonus)
	{
		return (open(file, O_CREAT | O_WRONLY | O_APPEND));
	}
	else
	{
		return (open(file, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
	}
}

void	execute_cmd(t_cmd *cmd, char **env)
{
	char	**args;
	char	*path;

	env++;
	path = find_path(cmd->cmd, env);
	execve(path, cmd->exec, env);
	write(STDERR, path, strlen_to_c(path, 0));
	write(STDERR, ": command not found\n", 20);
	exit(127);
}

void	redirect(int in, int out, t_cmd *cmd, char **env)
{
	int		ends[2];
	pid_t	parent;

	if (pipe(ends) < 0)
	{
		write(STDERR, "Couldn't open pipe!\n", 21);
		exit(-1);
	}
	parent = fork();
	if (parent)
	{
		dup2(ends[0], out);
		close(ends[1]);
		close(ends[0]);
		waitpid(parent, NULL, 0);
	}
	else
	{
		close(ends[0]);
		dup2(ends[1], in);
		if (in == STDIN)
			exit(1);
		else
			execute_cmd(cmd, env);
	}
}

void	eXecuTe(t_cmd *cmd, char **env)
{
	int	in;
	int	out;

	dup2(in, STDIN);
	dup2(out, STDOUT);
	// dup2(cmd->fd_in, STDIN);
	// dup2(cmd->fd_out, STDOUT);
	if (in < 0 || out < 0)
		return ;
	if (cmd->re_in)
		in = open_file(cmd->re_in, INFILE, 1);
	if (cmd->re_out)
		out = open_file(cmd->re_out, OUTFILE, 1);
	redirect(in, out, cmd, env);
	execute_cmd(cmd, env);
	write(STDERR, "ERROR! Invalid Syntax!\n", 23);
}
