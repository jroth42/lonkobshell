/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:08:18 by jroth             #+#    #+#             */
/*   Updated: 2022/04/26 23:44:14 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

int	g_exit = SUCCESS;

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

void	work_input(t_node *node, char **env)
{
	add_history(node->input);
	input_handle(node);
	lexer(node);
	change_termios(false);
	execute_loop(node->cmd, env);
	free_node(node->prev);
}

char	**return_env(char **env)
{
	static char	**environment;

	if (!environment)
		environment = env;
	return (*(&(environment)));
}

void	init_shell(char **env)
{
	t_node	*node;
	char	*prompt;

	prompt = ("lonkob@»-(٩(̾●̮̮̃̾•̃̾)۶)-> ...:  ");
	node = add_node(NULL);
	while (1)
	{
		handle_signals();
		node->input = readline(prompt);
		if (!node->input)
		{
			ft_putstr_fd("exit\n", 2);
			free_env();
			break ;
		}
		if (node->input != NULL && ft_strcmp(node->input, "") != 0)
			work_input(node, env);
		node = add_node(node);
	}
}

int	main(int argc, char **argv, char **env)
{
	(void) argv;
	(void) argc;
	get_env(env);
	return_env(env);
	init_shell(env);
	return (g_exit);
}
