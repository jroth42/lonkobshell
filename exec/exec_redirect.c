/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:52:07 by jroth             #+#    #+#             */
/*   Updated: 2022/04/06 19:01:32 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

// void	here_doc(t_exec *exec, t_cmd *cmd, char **env)
// {
// 	char	*line;

// 	line = readline("heredoc>");
// 	while (line)
// 	{
// 		if (!str_cmp_n(line, cmd->re_in, strlen_to_c(line, 0)))
// 			break ;
// 		write(exec->fd, line, strlen_to_c(line, 0));
// 		myfree(line);
// 		line = get_next_line(0);
// 	}
// 	myfree(line);
// 	close(exec->file_fd);
// 	dup2(exec->fd[READ], STDIN_FILENO);
// 	dup2(exec->fd[WRITE], STDOUT_FILENO);
// 	execute_cmd(cmd, env);
// }
	// if (cmd->re_type == LESSLESS)
	// 	here_doc(exec, cmd, env);
	// else

void	redirect_input(t_exec *exec, t_cmd *cmd, char **env)
{
	{	
		pipe(exec->fd);
		exec->pid = fork();
		if (exec->pid < 0)
			return ;
		if (exec->pid == 0)
		{
			dup2(exec->file_fd, STDIN_FILENO);
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
}

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
