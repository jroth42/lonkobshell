/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:14:09 by jroth             #+#    #+#             */
/*   Updated: 2022/03/18 19:04:09 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

char	*find_filename_left(char *input)
{
	int		i;
	int		j;
	int		k;
	i = 0;
	j = 0;
	if (input[i] == '>')
	{
		while (*(input - i) == ' ')
			i++;
		while (*(input - i - j) != ' ')
			j++;
	}
	return (ft_strdupn(input + j + i, j));
}

char	*find_filename_right(char *input)
{
	int		i;
	int		j;
	int		k;
	char	*file;

	i = 0;
	j = 0;
	if (input[i] == '<')
	{
		while (input[i] == ' ' || input[i] == '<')
			i++;
		while (input[i + j] != ' ')
			j++;
	}
	return (ft_strdupn(input + i, j));
}

void	handle_redirections(t_token *token, char **input)
{
	if (**input == '>' && **input + 1 == '>')
	{
		token->chr = ft_strjoin(find_filename_left(*input), ">>");
		token->type = GREATGREAT;
	}
	if (**input == '>')
	{
		token->chr = ft_strjoin(find_filename_left(*input), ">");
		printf("%s\n", token->chr);
		token->type = GREAT;
	}
	if (**input == '<' && **input + 1 == '<')
	{
		token->chr = ft_strjoin("<<", find_filename_right(*input));
		token->type = LESSLESS;
	}		
	if (**input == '<')
	{
		token->chr = ft_strjoin("<", find_filename_right(*input));
		printf("%s\n", token->chr);
		token->type = LESS;
	}
	if (token->chr != NULL)
		token = new_token(token);
}

void	handle_option(t_token *token, char **input)
{
	int		i;
	char	*str;

	i = 0;
	str = *input;
	if (str[i] == '-')
	{
		while (str[i] && !whitespace(str[i]))
			i++;
		token->chr = ft_strdupn(str, i);
		token->type = OPTION;
	}
	if (token->chr != NULL)
		token = new_token(token);
	(*input) += i;
}

void	handle_quotation(t_token *token, char **input)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	i = 0;
	str = *input;
	if (str[i++] == '\'')
	{
		while (str[i] != '\'')
			i++;
		if (str[i] == '\'')
		{
			token->chr = ft_strdupn((*input) + 1, i - 1);
			token->type = SQUOTE;
		}
	}
	else if (str[j++] == '\"')
	{
		while (str[j] && str[j] != '\"')
			j++;
		if (str[j] == '\"')
		{
			token->chr = ft_strdupn((*input) + 1, j - 1);
			token->type = DQUOTE;
		}
	}
	if (token->chr != NULL)
		token = new_token(token);
	(*input) += j + i + 1;
}

void	handle_word(t_token *token, char **input)
{
	int		i;
	char	*str;

	str = *input;
	i = 0;
	while (ft_isalpha(str[i]))
		i++;
	token->chr = ft_strdupn(*input, i);
	if ((token->prev && token->prev->type == PIPE)
		|| !token->prev)
		token->type = COMMAND;
	else
		token->type = ARG;
	if (token->chr)
		token = new_token(token);
	(*input) += i;
}
