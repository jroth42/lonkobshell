/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:44:17 by jroth             #+#    #+#             */
/*   Updated: 2022/04/18 22:35:12 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/shell.h"

static void	route_heredoc(t_exec *fds, t_redir *tmp)
{
	pipe(fds->here_fd);
	heredoc(tmp->file, fds, tmp->type);
	dup2(fds->here_fd[WRITE], STDOUT_FILENO);
	close(fds->here_fd[WRITE]);
}

static int	last_route(t_redir *last_in, t_exec *fds)
{
	if (last_in->type == LESS)
	{
		fds->file_fd = open_file(last_in->file, O_RDONLY, 0);
		if (fds->file_fd < 0)
		{
			free(fds);
			return (-1);
		}
		dup2(fds->file_fd, STDIN_FILENO);
		close(fds->file_fd);
	}
	else if (last_in->type == LESSLESS || last_in->type == LESSLESS + 1)
	{
		pipe(fds->here_fd);
		heredoc(last_in->file, fds, last_in->type);
		dup2(fds->here_fd[READ], STDIN_FILENO);
	}
	return (0);
}

int	route_stdin(t_cmd *cmd, t_exec *fds)
{
	t_redir	*last_in;

	last_in = get_last_in_redir(cmd->redirect);
	if (multiple_redir_in(cmd, fds) < 0)
	{
		free(fds);
		return (-1);
	}
	if (last_in)
	{
		if (last_route(last_in, fds) < 0)
			return (-1);
	}
	else if (!last_in)
	{
		dup2(fds->tmp_fd, STDIN_FILENO);
		close(fds->tmp_fd);
	}
	return (0);
}

int	multiple_redir_in(t_cmd *cmd, t_exec *fds)
{
	t_redir	*tmp;

	tmp = cmd->redirect;
	if (cmd->redirect && cmd->redirect->next && (cmd->redirect->next->type == LESS
			|| cmd->redirect->next->type == LESSLESS
			|| cmd->redirect->next->type == LESSLESS + 1))
	{
		while (tmp)
		{
			if (tmp->next && (tmp->type == LESS || tmp->type == LESSLESS
					|| tmp->type == LESSLESS + 1))
			{
				if (tmp->type == LESS)
				{
					fds->file_fd = open_file(tmp->file, O_RDONLY, 0);
					if (fds->file_fd < 0)
						return (-1);
				}
				if (tmp->type == LESSLESS)
					route_heredoc(fds, tmp);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}
