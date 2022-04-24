/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:08:18 by jroth             #+#    #+#             */
/*   Updated: 2022/04/24 23:58:19 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

int g_exit = SUCCESS;

// create node for each line of input
t_node	*add_node(t_node *node)
{
	t_node	*new;

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
	char	*prompt;
	
	(void) argv;
	(void) argc;
	prompt = ft_strdup("lonkob@»-(٩(̾●̮̮̃̾•̃̾)۶)-> ...:  ");
 	node = add_node(NULL);
	get_env(env);
	while (1)
	{
		handle_signals();
		node->input = readline(prompt);
		if (node->input != NULL && ft_strcmp(node->input, "") != 0)
		{
			add_history(node->input);
			input_handle(node);
			lexer(node);
			// if (g_exit == SUCCESS)
			{
				change_termios(false);
				execute_loop(node->cmd, env);
			}
			node = add_node(node);
		}
	}
	return (0);
}
