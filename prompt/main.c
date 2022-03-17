/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:08:18 by jroth             #+#    #+#             */
/*   Updated: 2022/03/18 00:13:29 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"


// create node for each line of input
t_node	*add_node(t_node *node)
{
	t_node *new;

	new = malloc(sizeof(t_node));
	new->input = NULL;
	new->next = NULL;
	new->prev = node;
	node->next = new;
	new->token = malloc(sizeof(t_token));
	return (new);
}

int	main(int argc, char **argv, char **env)
{
	t_node	*node;
	t_table	*table;

	node = malloc(sizeof(t_node));
	node->token = malloc(sizeof(t_token));
	while (1)
	{
		node->input = readline("\x1B[36mlonkobshell@»-(٩(̾●̮̮̃̾•̃̾)۶)->:\e[0m ");
		input_handle(node);
		add_history(node->input);
		lexer(node);
		node = add_node(node);
	}
	return (0);
}
