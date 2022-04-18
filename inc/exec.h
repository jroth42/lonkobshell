/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:36:05 by jroth             #+#    #+#             */
/*   Updated: 2022/04/18 23:22:39 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_exec
{
	pid_t	pid;
	int		fd[2];
	int		here_fd[2];
	int		tmp_fd;
	int		stin;
	int		stout;
	int		file_fd;
	int		cmd_count;
	int		no_rights;
	int		i;
}				t_exec;

void	execute_loop(t_cmd *cmd, char **env);
int		exec(t_cmd *cmd, char **env);

// REDIRECT
int		route_stdout(t_cmd *cmd, t_exec *fds);
int		route_stdin(t_cmd *cmd, t_exec *fds);
int		multiple_redir_in(t_cmd *cmd, t_exec *fds);
int		heredoc(char *delimiter, t_exec *fds, int type);
int		open_file(char *file, int mode, int rights);
char	*find_path(char *cmd, char **env);

// BUILTINS
bool	check_single_built_in(t_cmd *tm, char **env);
bool	check_builtin(t_cmd *table);
int		built_in_exec(t_cmd *table, char **env);

// UTILS

#endif
