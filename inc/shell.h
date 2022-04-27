/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:16:01 by jroth             #+#    #+#             */
/*   Updated: 2022/04/27 18:51:13 by jroth            ###   ########.fr       */
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

# define READ 0
# define WRITE 1
# define SIGINT 2
# define SIGQUIT 3
# define SUCCESS 0
# define FAIL 1

typedef struct s_string
{
	char	*str;
	int		len;
}	t_string;

extern int	g_exit;

char		**return_env(char **env);
// SIGN	LS
void		handle_signals(void);
void		sigint_handler(int sig);
int			change_termios(bool hide);
void		define_sig_prc(t_cmd *cmd);
void		sigint_handler_heredoc(int sig);
void		handle_pipe(t_string *t_str, t_token **token, char **input);
// FREE
void		myfree(void *mlc);
void		free_node(t_node *node);
void		free_token_list(t_token *token);
void		free_2d(char **exec);
//	----- UTILS ------ 
void		input_handle(t_node *node);
void		skip_white_space(char **str);
bool		white_space(const char c);
int			strlen_to_c(char *str, char c);
int			get_arr_size(char **arr);
int			error_msg(char *error_msg, int r_value);

//		STRBUILDER
t_string	*s_create(void);
void		s_copy(t_string *old, char **new);
int			s_reset(t_string *str);
char		*s_get_str(t_string *t_str);
int			s_add_c(t_string *str, const char c);
int			s_add_str(t_string *t_str, char *append);
int			s_add_int(t_string *t_str, int n);
int			s_add_strn(t_string *t_str, char *append, int len);
int			s_destroy(t_string *t_str);

// EXPAND && HEREDOC EXPAND
char		*get_word_envname(char **tmp);
void		dollar_expand(t_string **sb, char **tmp);
void		dollar_special_expand(t_string **t_str, char **input);
void		here_doc_print(t_exec *fds);
void		dquote_expand(t_string **sb, char **tmp);
void		expand_here(char **str);
// void	test_string(void);

#endif
