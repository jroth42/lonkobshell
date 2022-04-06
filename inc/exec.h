/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:36:05 by jroth             #+#    #+#             */
/*   Updated: 2022/04/06 18:28:54 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_exec
{
	pid_t	pid;
	int		fd[2];
	int		tmp_fd;
	int		file_fd;
}				t_exec;

void	execute(t_cmd *cmd, char **env);
void	redirect_output(t_exec *exec, t_cmd *cmd, char **env);
void	redirect_input(t_exec *exec, t_cmd *cmd, char **env);
int		execute_cmd(t_cmd *cmd, char **env);

void	check_redirects(t_exec *exec, t_cmd *cmd);
char	*find_path(char *cmd, char **env);
int		open_file(char *file, int mode, int type);

#endif
