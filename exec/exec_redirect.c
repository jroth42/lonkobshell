/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:52:07 by jroth             #+#    #+#             */
/*   Updated: 2022/04/05 18:52:19 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

int	open_file(char *file, int mode, int bonus)
{
	if (mode == INFILE)
	{
		if (access(file, F_OK))
		{
			write(STDERR_FILENO, "Couldn't find file: ", 21);
			write(STDERR_FILENO, file, strlen_to_c(file, 0));
			write(STDERR_FILENO, "\n", 1);
			return (STDIN_FILENO);
		}
		return (open(file, O_RDONLY));
	}
	else if (bonus)
	{
		return (open(file, O_CREAT | O_WRONLY | O_APPEND));
	}
	else
	{
		return (open(file, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
	}
}
