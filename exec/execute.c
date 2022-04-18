/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:03:58 by jroth             #+#    #+#             */
/*   Updated: 2022/04/06 19:23:20 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

int	execute_cmd(t_cmd *cmd, char **env)
{
	char	*path;

	env++;
	path = find_path(cmd->cmd, env);
	execve(path, cmd->exec, env);
	write(STDERR_FILENO, "lonkobshell: ", 13);
	write(STDERR_FILENO, cmd->cmd, ft_strlen(cmd->cmd));
	write(STDERR_FILENO, ": command not found\n", 20);
	return (127);
}

void	pipe_it(t_exec *exec, t_cmd *cmd, char **env)
{
	if (cmd->re_out)
		redirect_output(exec, cmd, env);
	pipe(exec->fd);
	exec->pid = fork();
	if (exec->pid < 0)
		return ;
	if (exec->pid == 0)
	{
		dup2(exec->tmp_fd, STDIN_FILENO);
		dup2(exec->fd[WRITE], STDOUT_FILENO);
		close(exec->fd[WRITE]);
		close(exec->tmp_fd);
		execute_cmd(cmd, env);
	}
	else
	{
		wait(NULL);
		close(exec->fd[WRITE]);
		close(exec->tmp_fd);
		exec->tmp_fd = dup(exec->fd[READ]);
		close(exec->fd[READ]);
	}
}

void	write_it(t_exec *exec, t_cmd *cmd, char **env)
{
	if (cmd->re_out)
		redirect_output(exec, cmd, env);
	else
		exec->pid = fork();
	if (exec->pid == 0)
	{
		dup2(exec->tmp_fd, STDIN_FILENO);
		execute_cmd(cmd, env);
		close(exec->tmp_fd);
	}
	else
	{
		close(exec->tmp_fd);
		wait(NULL);
		exec->tmp_fd = dup(STDIN_FILENO);
	}
}

void	execute(t_cmd *cmd, char **env)
{
	t_exec	exec;
	t_cmd	*tmp;

	tmp = cmd;
	check_redirects(&exec, cmd);
	exec.tmp_fd = dup(STDIN_FILENO);
	while (cmd)
	{
		if (cmd->next)
			pipe_it(&exec, cmd, env);
		else if (!cmd->next)
			write_it(&exec, cmd, env);
		cmd = cmd->next;
	}
	close(exec.fd[READ]);
	close(exec.fd[WRITE]);
	close(exec.tmp_fd);
	close(exec.file_fd);
}
	// free_cmd_list(tmp);
