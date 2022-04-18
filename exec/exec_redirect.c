/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:52:07 by jroth             #+#    #+#             */
/*   Updated: 2022/04/06 19:21:38 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

void	redirect_output(t_exec *exec, t_cmd *cmd, char **env)
{
	pipe(exec->fd);
	exec->pid = fork();
	if (exec->pid < 0)
		return ;
	if (exec->pid == 0)
	{
		dup2(exec->file_fd, STDOUT_FILENO);
		close(exec->file_fd);
		execute_cmd(cmd, env);
	}
	else
	{
		wait(NULL);
		exec->tmp_fd = dup(exec->fd[READ]);
		close(exec->tmp_fd);
		close(exec->file_fd);
	}
}
