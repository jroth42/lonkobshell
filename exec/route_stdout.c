/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_stdout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:43:58 by jroth             #+#    #+#             */
/*   Updated: 2022/04/25 16:12:22 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

int	route_out(int type, t_redir *out)
{
	if (type == TRUNCATE)
	{
		open(out->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (access(out->file, W_OK) < 0)
			return (-1);
	}
	else if (type == APPEND)
	{
		open(out->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (access(out->file, W_OK) < 0)
			return (-1);
	}
	return (0);
}

t_redir	*get_last_out_redir(t_redir *head)
{
	t_redir	*out;

	out = NULL;
	while (head)
	{
		if (head->type == TRUNCATE || head->type == APPEND)
		{
			out = head;
			if (route_out(head->type, out) < 0)
				break ;
		}
		head = head->next;
	}
	return (out);
}

int	last_redir_out(t_exec *fds, t_redir *last_out)
{
	if (last_out->type == TRUNCATE)
	{
		fds->file_fd = open_file(last_out->file,
				O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fds->file_fd < 0)
			return (-1);
		dup2(fds->file_fd, STDOUT_FILENO);
		close(fds->file_fd);
	}
	if (last_out->type == APPEND)
	{
		fds->file_fd = open_file(last_out->file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fds->file_fd < 0)
			return (-1);
		dup2(fds->file_fd, STDOUT_FILENO);
		close(fds->file_fd);
	}
	return (0);
}

void	handle_redir_out(t_cmd *cmd, t_exec *fds)
{
	if (!cmd->next)
	{
		if (fds->here_fd[READ] > 0 || fds->here_fd[WRITE] > 0)
		{
			dup2(fds->stout, fds->here_fd[WRITE]);
			close(fds->stout);
		}
		dup2(fds->stout, STDOUT_FILENO);
		close(fds->stout);
	}
	else
	{
		if (fds->here_fd[READ] > 0 || fds->here_fd[WRITE] > 0)
		{
			dup2(fds->fd[READ], fds->here_fd[WRITE]);
			close(fds->fd[READ]);
		}
		dup2(fds->fd[WRITE], STDOUT_FILENO);
		close(fds->fd[WRITE]);
	}
}

int	route_stdout(t_cmd *cmd, t_exec *fds)
{
	t_redir	*last_out;

	last_out = get_last_out_redir(cmd->redirect);
	if (last_out)
	{
		if (last_redir_out(fds, last_out) < 0)
			return (-1);
	}
	else if (!last_out)
		handle_redir_out(cmd, fds);
	return (0);
}
