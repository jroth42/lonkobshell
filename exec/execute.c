/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:03:58 by jroth             #+#    #+#             */
/*   Updated: 2022/04/04 13:50:46 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

int	open_file(char *file, int mode, int bonus)
{
	if (mode == INFILE)
	{
		if (access(file, F_OK))
		{
			write(STDERR_FILENO, "Couldn't find file: ", 21);
			write(STDERR_FILENO, file, strlen_to_c(file, 0));
			write(STDERR_FILENO, "\n", 1);
			return (STDIN_FILENO);
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

static int	execute_cmd(t_cmd *cmd, char **env)
{
	char	**args;
	char	*path;

	env++;
	path = find_path(cmd->cmd, env);
	execve(path, cmd->exec, env);
	return (127);
}

void	eXecuTe(t_cmd *cmd, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		tmp_fd;
	
	tmp_fd = dup(STDIN_FILENO);
	while (cmd)
	{
		if (cmd->next)
		{
			pipe(fd);
			pid = fork();
			if (pid < 0)
				return ;
			if (pid == 0)
			{
				dup2(tmp_fd, STDIN_FILENO);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				close(tmp_fd);
				execute_cmd(cmd, env);
			}
			else
			{
				close(fd[1]);
				close(tmp_fd);
				wait(NULL);
				tmp_fd = dup(fd[0]);
				close(fd[0]);
			}
		}
		else if (!cmd->next)
		{
			pid = fork();
			if (pid == 0)
			{
				dup2(tmp_fd, STDIN_FILENO);
				execute_cmd(cmd, env);
				close(tmp_fd);
			}
			else
			{
				close(tmp_fd);
				waitpid(-1, NULL, WUNTRACED);
				tmp_fd = dup(STDIN_FILENO);
			}
		}
		cmd = cmd->next;
	}
}
