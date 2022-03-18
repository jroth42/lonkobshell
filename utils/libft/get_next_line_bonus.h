/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:31:39 by jroth             #+#    #+#             */
/*   Updated: 2022/03/18 16:08:02 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*bigbuff(char	**newline);
char	*ireturn(char	**newline, size_t rd);
char	*ijoin(char *nl, char *bf);
int		isearchlen(const char *s, char c);
size_t	sublen(size_t i, char *str);
void	*icalloc(size_t count, size_t size);
char	*isubstring(char *str, unsigned int start, size_t len);
void	ifree(char **str);
#endif
