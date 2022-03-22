// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   cmdtable.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/03/15 14:23:37 by jroth             #+#    #+#             */
// /*   Updated: 2022/03/15 22:19:34 by jroth            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../inc/shell.h"

t_table	*create_cmd(t_table *table)
{
	t_table *new;

	new = malloc(sizeof(t_table));
	if (!new)
		return (NULL);
	new->exec = NULL;
	new->args = NULL;
	new->re_in = NULL;
	new->re_out = NULL;
	new->next = NULL;
	if (!table)
	{
		new->prev = NULL;
		return (new);
	}
	else
	{
		new->prev = table;
		table->next = new;
	}
	return (new);
}


void	fill_arguments(t_token **token, t_table **table)
{
	t_token	*tmp;
	char	*join;
	char	*copy;

	tmp = *token;
	copy = NULL;
	join = NULL;
	if ((*table)->args)
	{
		while (tmp && tmp->type != PIPE)
		{
			if (tmp->type == ARG)
			{
				join = ft_strjoin((*table)->args, " ");
				copy = join;
				join = ft_strjoin(copy, tmp->chr);
				(*table)->args = join;
			
			}
			tmp = tmp->next;
		}
	}
	else
		(*table)->args = ft_strdup(tmp->chr);
}

void	command_table(t_node *node)
{
	t_token	*tmp;

	tmp = node->token;
	while (tmp && tmp->prev)
		tmp = tmp->prev;
	node->table = create_cmd(NULL);
	while (tmp->next)
	{
		if (tmp->type == COMMAND)
			(node)->table->exec = ft_strdup(tmp->chr);
		if (tmp->type == ARG)
			fill_arguments(&tmp, &(node)->table);
		if (tmp->type == GREAT || tmp->type == GREATGREAT)
			(node)->table->re_out = ft_strdup(tmp->chr);
		if (tmp->type == LESS || tmp->type == LESSLESS)
			(node)->table->re_in = ft_strdup(tmp->chr);
		if (tmp->type == PIPE)
		{
			(node)->table->next = create_cmd(node->table);
			node->table = node->table->next;
		}
		tmp = tmp->next;
	}
}
