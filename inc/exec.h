/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:36:05 by jroth             #+#    #+#             */
/*   Updated: 2022/04/05 18:54:42 by jroth            ###   ########.fr       */
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

char	*find_path(char *cmd, char **env);
void	execute(t_cmd *cmd, char **env);
int		strlen_to_c(char *str, char c);

#endif