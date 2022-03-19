/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:08:18 by jroth             #+#    #+#             */
/*   Updated: 2022/03/19 20:41:57 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"


// create node for each line of input
t_node	*add_node(t_node *node)
{
	t_node *new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->input = NULL;
	new->next = NULL;
	if (node)
	{
		new->prev = node;
		node->next = new;	
	}
	else
	{
		new->prev = NULL;
		new->next = NULL;	
	}
	new->token = create_token(NULL);
	return (new);
}

int	main(int argc, char **argv, char **env)
{
	t_node	*node;
	t_table	*table;

	node = add_node(NULL);
	while (1)
	{ 
		node->input = readline("lonkob@»-(٩(̾●̮̮̃̾•̃̾)۶)->...: ");
		add_history(node->input);
		input_handle(node);
		lexer(node);
		node = add_node(node);
	}
	return (0);
}
