/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:31:42 by jroth             #+#    #+#             */
/*   Updated: 2022/03/19 16:34:20 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

// printfuncttions for testing

void	print_tokens(t_node	*node)
{
	t_token *token;

	token = node->prev->token;
	while (token && token->prev)
		token = token->prev;
	printf("--------------------\n");
	while (token->next)
	{
		printf("Chars:\t%s\nType:\t%d\n", token->chr, token->type);
		printf("--------------------\n");
		token = token->next;
	}
}

void	print_nodes(t_node	*node)
{
	int i;

	i = 0;
	node = node->prev;
	while (node)
	{
		printf("Node%d\t%s\n", ++i, node->input);
		node = node->prev;
	}
}

bool	stringcmp(char *str, char *cmp)
{
	if (str && cmp)
	{
		if (ft_strlen(str) != ft_strlen(cmp))
			return (false);
		while (*str)
		{
			if (!(*str) || !(*cmp))
				return (false);
			if (*str != *cmp)
				return (false);
			str++;
			cmp++;
		}
		return (true);
	}
	return (false);
}

void	input_handle(t_node *node)
{
	if (node->prev)
	{
		if (stringcmp("token", node->input))
			print_tokens(node);
		if (stringcmp("nodes", node->input))
			print_nodes(node);
	}
		if (stringcmp("exit", node->input))
			exit(0);
}