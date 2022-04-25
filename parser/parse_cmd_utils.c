/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 01:07:09 by jroth             #+#    #+#             */
/*   Updated: 2022/04/26 01:10:19 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

void	pipe_cmd_handle(t_node **node)
{
		(*node)->cmd->next = create_cmd((*node)->cmd);
		(*node)->cmd = (*node)->cmd->next;
}

void	fill_arguments(t_token *token, t_cmd **cmd)
{
	char	*join;
	char	*copy;

	if ((*cmd)->args)
	{
		copy = ft_strjoin((*cmd)->args, " ");
		join = ft_strjoin(copy, token->chr);
		(*cmd)->args = join;
	}
	else
		(*cmd)->args = ft_strdup(token->chr);
}
