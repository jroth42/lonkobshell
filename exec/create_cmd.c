/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:44:23 by jroth             #+#    #+#             */
/*   Updated: 2022/03/30 18:43:23 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

char	**create_exec(t_node *node)
{
	char	**args;
	static t_token	*token;
	int		i;

	i = 0;
	token = node->token;
	while (token && token->prev)
	{
		token = token->prev;
		i++;
	}
	args = malloc(sizeof(char *) * (i));
	i = 0;
	while (token->next)
	{
		if (token->type == PIPE)
			break ;
		args[i] = token->chr;
		token = token->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
