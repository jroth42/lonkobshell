/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:15:02 by jroth             #+#    #+#             */
/*   Updated: 2022/04/26 21:20:52 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

t_redir	*new_redir(char *file, int type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = type;
	new->file = file;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_redir	*get_last_redir(t_redir *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

t_redir	*append_redir(t_redir **head, t_redir *new)
{
	t_redir	*last;

	if (!(*head))
		*head = new;
	else
	{
		last = get_last_redir(*head);
		last->next = new;
		new->prev = last;
	}
	return (new);
}

t_redir	*get_last_in_redir(t_redir *head)
{
	t_redir	*in;

	if (!head)
		return (NULL);
	in = NULL;
	while (head)
	{
		if (head->type == READ_INPUT || head->type == HEREDOC
			|| head->type == HEREDOC + 1)
		{
			in = head;
			if (head->type == READ_INPUT)
			{
				if (access(in->file, R_OK) < 0)
				{
					g_exit = 1;
					break ;
				}
			}
		}
		head = head->next;
	}
	return (in);
}

void	add_redirection(t_token *tmp, t_redir **redir)
{
	if (!ft_strcmp(tmp->chr, ""))
		error_msg("syntax error near unexpected token 'newline'", FAIL);
	else if (!(*redir))
		*redir = new_redir(tmp->chr, tmp->type);
	else
		append_redir(redir, new_redir(tmp->chr, tmp->type));
}
