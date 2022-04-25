/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:19:05 by jroth             #+#    #+#             */
/*   Updated: 2022/04/25 23:19:20 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

bool	parser_error(t_token *token)
{
	char		*str;
	t_string	*sb;
	char		*err_msg;

	if (token->type == -5)
	{
		str = token->chr;
		sb = s_create();
		if (ft_strlen(str) > 2)
			str = ft_substr(str, 0, 2);
		s_add_str(sb, "syntax error: near unexpected token '");
		s_add_str(sb, str);
		s_add_c(sb, '\'');
		err_msg = s_get_str(sb);
		s_destroy(sb);
		g_exit = error_msg(err_msg, 258);
		myfree(err_msg);
		return (true);
	}
	return (false);
}

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

//	go through all the characters, skip white_spaces, 
//	create tokens for args, commands, redirects... -> handle_token.c
//	... move Pointer within each function with **ptr 
//		-> (*ptr) += chars to be skipped.
//	afterwards send to cmd parser
void	handle_forbidden_and_pipe(t_token **token, char **input)
{
	t_string	*t_str;

	t_str = s_create();
	if ((**input) == '&')
	{
		while (**input == '&')
		{
			s_add_c(t_str, '&');
			(*input)++;
		}
		(*token)->type = -5;
	}
	else if (**input == '|')
		handle_pipe(t_str, token, input);
	if (!(*token)->chr)
		(*token)->chr = s_get_str(t_str);
	if ((*token)->chr)
		*token = create_token(*token);
	s_destroy(t_str);
}

// static void	valid_quotes(t_token **token)
// {
// 	t_string	*t_str;
// 	t_token		*tmp;

// 	tmp = *token;
// 	t_str = s_create();
// 	while (tmp->type == SQUOTE || tmp->type == DQUOTE)
// 	{
// 		while (*(tmp->chr))
// 		{
// 			if (*tmp->chr != '\'' || *tmp->chr != '\"')
// 				s_add_c(t_str, *tmp->chr);
// 			tmp->chr++;
// 		}
// 		tmp = tmp->next;
// 	}
// 	printf("%s\n", t_str->str);
// 	if (access(tmp->chr, F_OK))
// 		tmp->type = COMMAND;
// 	else
// 		tmp->type = ARG;
// 	*token = tmp;
// }

void	lexer(t_node *node)
{
	char	*input;

	input = node->input;
	while (*input)
	{
		if (white_space(*input))
			skip_white_space(&input);
		else if ((*input == '\"' || *input == '\'' || *input == '$'))
			expander(&node->token, &input);
		else if (*input == '>' || *input == '<')
			handle_redirections(&node->token, &input);
		else if (*input == '&' || (*input == '|'))
			handle_forbidden_and_pipe(&node->token, &input);
		else
			handle_word(&node->token, &input);
	}
	parse_cmd(node);
}
