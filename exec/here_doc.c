/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:53:26 by jroth             #+#    #+#             */
/*   Updated: 2022/04/18 22:02:52 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

int	change_termios(bool hide)
{
	struct termios	term;

	if (tcgetattr(STDOUT_FILENO, &term) == -1)
		return (1);
	if (hide)
		term.c_lflag &= ~(ECHOCTL);
	else
		term.c_lflag |= ECHOCTL;
	if (tcsetattr(STDOUT_FILENO, TCSANOW, &term) == -1)
		return (1);
	return (0);
}

static void	here_doc_print(t_exec *fds)
{
	while (fds->cmd_count)
	{
		write(0, "> ", 2);
		fds->cmd_count--;
	}
	write(0, "> ", 2);
}

int	heredoc(char *delimiter, t_exec *fds, int type)
{
	char	*read;
	char	*delimiter_nl;

	delimiter_nl = ft_strjoin(delimiter, "\n");
	// signal(SIGINT, sigint_handler_heredoc);
	while (true)
	{
		here_doc_print(fds);
		read = get_next_line(STDIN_FILENO);
		if (!read || !ft_strcmp(read, delimiter_nl))
		{
			if (!read)
				write(2, "\n", 1);
			break ;
		}
		(void) type;
		// if (type == 240)
		// 	expand(&read);
		write(fds->here_fd[WRITE], read, ft_strlen(read));
		myfree((void **)&read);
	}
	change_termios(false);
	close(fds->here_fd[WRITE]);
	myfree((void **)&read);
	myfree((void **)&delimiter_nl);
	return (EXIT_SUCCESS);
}