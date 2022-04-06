/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:16:01 by jroth             #+#    #+#             */
/*   Updated: 2022/04/06 16:42:08 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../utils/libft/libft.h"
# include "parser.h"
# include "exec.h"

# define INFILE 0
# define OUTFILE 1
# define READ 0
# define WRITE 1

//	----- UTILS ------ 
void	input_handle(t_node *node);
void	skip_whitespace(char **str);
bool	whitespace(const char c);
int		strlen_to_c(char *str, char c);

// FREE
void	myfree(void *mlc);
void	free_token_list(t_token *token);
void	free_cmd_list(t_cmd *cmd);

#endif