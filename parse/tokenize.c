/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:19:05 by jroth             #+#    #+#             */
/*   Updated: 2022/04/05 19:38:17 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

//	creates list of tokens if !token otherwise appends tokens to list
t_token	*create_token(t_token *token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->chr = NULL;
	new->type = COMMAND;
	new->next = NULL;
	if (!token)
	{
		new->prev = NULL;
		return (new);
	}
	else
	{
		new->prev = token;
		token->next = new;
	}
	return (new);
}

//	go through all the characters, skip whitespaces, 
//	create tokens for args, commands, redirects... -> handle_token.c
//	... move Pointer within each function with **ptr 
//		-> (*ptr) += chars to be skipped.
//	afterwards send to cmd parser
void	lexer(t_node *node)
{
	char	*input;

	input = node->input;
	while (*input)
	{
		if (whitespace(*input))
			skip_whitespace(&input);
		else if (*input == '\"' || *input == '\'')
			handle_quotation(&node->token, &input);
		else if (*input == '>' || *input == '<')
			handle_redirections(&node->token, &input);
		else if (*input == '|')
			handle_pipe(&node->token, &input);
		else
			handle_word(&node->token, &input);
	}
	parse_cmd(node);
}