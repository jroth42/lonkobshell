/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:16:01 by jroth             #+#    #+#             */
/*   Updated: 2022/04/19 21:30:47 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <limits.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>

# include "../utils/libft/libft.h"
# include "parser.h"
# include "exec.h"
# include "built_in.h"

# define INFILE 0
# define OUTFILE 1
# define READ 0
# define WRITE 1
# define SIGINT 2
# define SIGQUIT 3
# define SUCCESS 0
# define FAIL 1

extern int	g_exit;

//	----- UTILS ------ 
void	input_handle(t_node *node);
void	skip_white_space(char **str);
bool	white_space(const char c);
int		strlen_to_c(char *str, char c);

// SIGNALS
void	handle_signals(void);
void	sigint_handler(int sig);
int		change_termios(bool hide);
void	define_sig_prc(t_cmd *cmd);
void	sigint_handler_heredoc(int sig);

// FREE
void	myfree(void *mlc);
void	free_node(t_node *node);

#endif
