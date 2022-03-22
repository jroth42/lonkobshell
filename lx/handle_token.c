/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:14:09 by jroth             #+#    #+#             */
/*   Updated: 2022/03/22 13:43:22 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

void	handle_pipe(t_token **token, char **input)
{
	(*token)->chr = ft_strdup("|");
	(*token)->type = PIPE;
	if ((*token)->chr)
		*token = create_token(*token);
	(*input)++;
}

void	handle_dquote(t_token **token, char **input)
{
	int		i;
	char	*str;

	i = 0;
	str = *input;
	if (str[i] == '\"' && str[i + 1] == '\"')
	{
		(*input) += 2;
		return ;
	}
	if (str[i++] == '\"')
	{
		while (str[i] != '\"')
			i++;
		if (str[i] == '\"')
		{
			(*token)->chr = ft_strdupn((*input), ++i);
			(*token)->type = DQUOTE;
		}
	}
	if ((*token)->chr)
		*token = create_token(*token);
	(*input) += i;
}

void	handle_squote(t_token **token, char **input)
{
	int		i;
	char	*str;

	i = 0;
	str = *input;
	if (str[i] == '\'' && str[i + 1] == '\'')
	{
		(*input) += 2;
		return ;
	}
	if (str[i++] == '\'')
	{
		while (str[i] != '\'')
			i++;
		if (str[i] == '\'')
		{
			(*token)->chr = ft_strdupn((*input), ++i);
			(*token)->type = SQUOTE;
		}
	}
	if ((*token)->chr)
		*token = create_token(*token);
	(*input) += i;
}

void	handle_quotation(t_token **token, char **input)
{
	if (**input == '\'')
		handle_squote(token, input);
	if (**input == '\"')
		handle_dquote(token, input);
}

void	handle_word(t_token **token, char **input)
{
	char	*str;
	int		i;
	int		type;

	str = *input;
	i = 0;
	while (str[i] == '-' || ft_isalpha(str[i]) || ft_isdigit(str[i]))
		i++;
	(*token)->chr = ft_strdupn(*input, i);
	if ((*token)->prev)
	{
		type = (*token)->prev->type;
		if (type != PIPE)
			(*token)->type = ARG;
		if (type == LESS || type == LESSLESS)
			(*token)->type = COMMAND; 
		if (type == GREAT || type == GREATGREAT)
			(*token)->type = COMMAND; 
	}
	if ((*token)->chr)
		*token = create_token(*token);
	(*input) += i;
}
