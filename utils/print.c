/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:31:42 by jroth             #+#    #+#             */
/*   Updated: 2022/04/26 01:40:29 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

// // printfuncttions for testing
int	error_msg(char *error_msg, int r_value)
{
	ft_putstr_fd("lonkob: ", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putchar_fd('\n', 2);
	return (r_value);
}

void	print_cmd(t_node *node)
{
	int		i;
	t_cmd	*cmd;

	if (node->cmd)
	{
		cmd = node->cmd;
		i = 0;
		while (cmd && cmd->prev)
			cmd = cmd->prev;
		printf("------------------\n");
		while (cmd)
		{
			printf("COMMAND %d:\n", ++i);
			if (cmd->cmd)
				printf("exec:\t%s\n", cmd->cmd);
			if (cmd->args)
				printf("args:\t%s\n", cmd->args);
			printf("------------------\n");
			cmd = cmd->next;
		}	
	}
}

void	print_tokens(t_node	*node)
{
	t_token	*token;

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

// void	print_nodes(t_node *node)
// {
// 	int	i;

// 	i = 0;
// 	while (node)
// 	{
// 		printf("Node%d\t%s\n", ++i, node->input);
// 		node = node->prev;
// 	}
// }

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
	if (node && node->prev)
	{
		if (stringcmp("token", node->input))
			print_tokens(node->prev);
		if (stringcmp("cmd", node->input))
			print_cmd(node->prev);
	}
}

// void	input_handle(t_node *node)
// {
// 	if (node)
// 	{
// 		if (stringcmp("pwd", node->input))
// 			node++;//insert function
// 	}
// 	if (stringcmp("exit", node->input))
// 		exit(0);
// }
