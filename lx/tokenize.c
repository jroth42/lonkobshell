/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:19:05 by jroth             #+#    #+#             */
/*   Updated: 2022/03/18 18:59:10 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"


// allocate token and NULL it
t_token	*create_token(void)
{
	t_token	*new;
	new = malloc(sizeof(t_token));
	new->chr = NULL;
	new->type = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

// create a new token, and append to given list
t_token	*new_token(t_token *token)
{
	t_token	*tmp;

	if (!token)
	{
		tmp = create_token();
		return (tmp);
	}
	else
	{
		tmp = token;
		token = create_token();
		token->prev = tmp;
		tmp->next = token;
	}
	return (token);
}

// IN THEORY: go through all the characters, skip whitespaces, 
// create tokens for args, options, commands, redirects... -> handle_token.c
// ... Move Pointer within each function **ptr
void	lexer(t_node *node)
{
	char	*input;
	int		i;

	i = 0;
	input = node->input;
	while (*input)
	{
		if (whitespace(*input))
			skip_whitespace(&input);
		if (*input == '-')
			handle_option(node->token, &input);
		else if (*input == '\"' || *input == '\'')
			handle_quotation(node->token, &input);
		else if (ft_isalpha(*input))
			handle_word(node->token, &input);

		// else if (*input == '>' || *input == '<')
		// 	handle_redirections(node->token, &input);
		// else if (*input == '-')
		// 	handle_option(node->token, &input);
		// else
	}
}
