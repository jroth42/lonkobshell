/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:48:50 by jroth             #+#    #+#             */
/*   Updated: 2022/04/25 15:37:05 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

void	sigint_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		change_termios(false);
		g_exit = FAIL;
		exit(g_exit);
	}
}

void	sigchild_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_exit = 130;
	}
	if (sig == SIGQUIT)
	{
		write(2, "Quit: 3\n", 9);
		g_exit = SUCCESS;
	}
}

static bool	check_heredoc(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == HEREDOC || redir->type == HEREDOC + 1)
			return (true);
		redir = redir->next;
	}
	return (false);
}

void	define_sig_prc(t_cmd *cmd)
{
	if (check_heredoc(cmd->redirect))
	{
		change_termios(true);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, sigchild_handler);
		signal(SIGQUIT, sigchild_handler);
	}
}

int	change_termios(bool hide)
{
	struct termios	term;

	if (tcgetattr(STDOUT_FILENO, &term) == -1)
		return (FAIL);
	if (hide)
		term.c_lflag &= ~(ECHOCTL);
	else
		term.c_lflag |= ECHOCTL;
	if (tcsetattr(STDOUT_FILENO, TCSANOW, &term) == -1)
		return (FAIL);
	return (SUCCESS);
}
