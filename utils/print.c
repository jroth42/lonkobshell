/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:31:42 by jroth             #+#    #+#             */
/*   Updated: 2022/03/22 18:55:56 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

// printfuncttions for testing

void	print_table(t_node *node)
{
	int	i;
	t_table	*table;

	table = node->table;
	i = 0;
	while (table && table->prev)
		table = table->prev;
	while (table)
	{
		printf("------------------\n");
		printf("COMMAND %d:\n", ++i);
		if (table->exec)
			printf("exec:\t%s\n", table->exec);
		if (table->args)
			printf("args:\t%s\n", table->args);
		if (table->re_in)
			printf("re_in:\t%s\n", table->re_in);
		if (table->re_out)
			printf("re_out:\t%s\n", table->re_out);
		printf("------------------\n");
		table = table->next;
	}
}

void	print_tokens(t_node	*node)
{
	t_token *token;

	token = node->token;
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

void	print_nodes(t_node *node)
{
	int i;

	i = 0;
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
			print_tokens(node->prev);
		if (stringcmp("node", node->input))
			print_nodes(node->prev);
		if (stringcmp("table", node->input))
			print_table(node->prev);
	}
		if (stringcmp("exit", node->input))
			exit(0);
}
