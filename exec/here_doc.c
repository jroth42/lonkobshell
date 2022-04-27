/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:53:26 by jroth             #+#    #+#             */
/*   Updated: 2022/04/27 18:57:00 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

void	squote_no_expand(t_string **sb, char **tmp)
{
	int	i;

	i = 1;
	while ((*tmp)[i] && (*tmp)[i] != SQUOTE)
		i++;
	if ((*tmp)[i] == SQUOTE)
		i++;
	s_add_strn(*sb, *tmp, i);
	*tmp += i;
}

void	expand_here(char **str)
{
	t_string	*sb;
	char		*tmp;

	sb = s_create();
	tmp = *str;
	while (*tmp)
	{
		if (*tmp == '$')
			dollar_expand(&sb, &tmp);
		else if (*tmp == DQUOTE)
			dquote_expand(&sb, &tmp);
		else if (*tmp == SQUOTE)
			squote_no_expand(&sb, &tmp);
		else
		{
			s_add_c(sb, *tmp);
			tmp++;
		}
	}
	*str = s_get_str(sb);
	s_destroy(sb);
}

int	heredoc(char *delimiter, t_exec *fds, int type)
{
	char	*read;
	char	*delimiter_nl;

	delimiter_nl = ft_strjoin(delimiter, "\n");
	signal(SIGINT, sigint_handler_heredoc);
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
		if (type == 240)
			expand_here(&read);
		write(fds->here_fd[WRITE], read, (int) ft_strlen(read));
	}
	change_termios(false);
	close(fds->here_fd[WRITE]);
	myfree(read);
	myfree(delimiter_nl);
	return (EXIT_SUCCESS);
}
