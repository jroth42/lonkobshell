/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:03:58 by jroth             #+#    #+#             */
/*   Updated: 2022/04/26 23:35:22 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

static int	create_prcs(t_cmd *cmd, t_exec *fds, char **env)
{
	pipe(fds->fd);
	define_sig_prc(cmd);
	fds->i++;
	fds->pid = fork();
	if (fds->pid == 0)
	{
		close(fds->fd[READ]);
		if (!cmd->prev && !cmd->next
			&& !cmd->redirect && !check_builtin(cmd))
				g_exit = exec(cmd, env);
		else
		{
			if (route_stdin(cmd, fds) < 0)
				exit(1);
			if (route_stdout(cmd, fds) < 0)
				exit(1);
			g_exit = exec(cmd, env);
		}
	}
	close(fds->tmp_fd);
	dup2(fds->fd[READ], fds->tmp_fd);
	close(fds->fd[READ]);
	close(fds->fd[WRITE]);
	return (fds->pid);
}

static void	end_prcs(t_exec *fds)
{
	close(fds->stin);
	close(fds->stout);
	close(fds->tmp_fd);
	while (fds->i > 0)
	{
		waitpid(0, &fds->pid, 0);
		if (WIFEXITED(fds->pid))
			g_exit = WEXITSTATUS(fds->pid);
		fds->i--;
	}
}

void	set_exec(t_exec *exec)
{
	exec->fd[READ] = 0;
	exec->fd[WRITE] = 0;
	exec->here_fd[READ] = 0;
	exec->here_fd[WRITE] = 0;
	exec->stin = dup(STDIN_FILENO);
	exec->stout = dup(STDOUT_FILENO);
	exec->tmp_fd = dup(STDIN_FILENO);
	exec->file_fd = 0;
	exec->cmd_count = 0;
	exec->no_rights = 0;
	exec->pid = 0;
	exec->i = 0;
}

int	exec(t_cmd *cmd, char **env)
{
	char	*path;

	if (check_builtin(cmd))
		built_in_exec(cmd);
	path = find_path(cmd->cmd, env);
	if (!path)
		perror("Could not resolve environ array.\n");
	else if (cmd->exec)
	{
		execve(path, cmd->exec, env);
		ft_putstr_fd("lonkob: ", STDERR_FILENO);
		ft_putstr_fd(cmd->cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		g_exit = 127;
		exit(g_exit);
	}
	exit(SUCCESS);
}

void	execute_loop(t_cmd *cmd, char **env)
{
	t_cmd	*tmp;
	t_exec	exec;

	tmp = cmd;
	set_exec(&exec);
	while (tmp)
	{
		if (!tmp->cmd && !tmp->redirect)
		{
			tmp = tmp->next;
			continue ;
		}
		if (check_single_built_in(tmp))
			break ;
		else
		{
			if (create_prcs(tmp, &exec, env) < 0)
			{
				g_exit = FAIL;
				break ;
			}
		}
		tmp = tmp->next;
	}
	end_prcs(&exec);
}
