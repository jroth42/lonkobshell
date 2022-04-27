/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 21:46:18 by jroth             #+#    #+#             */
/*   Updated: 2022/04/26 23:59:25 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signals(void)
{
	change_termios(true);
	signal(SIGQUIT, sigint_handler);
	signal(SIGINT, sigint_handler);
}

char	**return_env(char **env)
{
	static char	**environment;

	if (!environment)
		environment = env;
	return (*(&(environment)));
}
