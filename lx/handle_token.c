/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:14:09 by jroth             #+#    #+#             */
/*   Updated: 2022/03/18 00:10:52 by jroth            ###   ########.fr       */
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
	int	i;

	i = 0;
	if (*input[i] == '-')
	{
		while (*input[i] && *input[i] != ' ')
			i++;
		token->chr = ft_strdupn(*input, i);
		token->type = OPTION;
	}
	if (token->chr != NULL)
		token = new_token(token);
}

void	handle_quotation(t_token *token, char **input)
{
	int	i;

	i = 0;
	if ((**input)++ == '\'')
	{
		while (*input[i] != '\'')
			i++;
		if (*input[i] == '\'')
		{
			token->chr = ft_strdupn(*input, i);
			token->type = SQUOTE;
		}
	}	
	else if ((**input)++ == '\"')
	{
		while (*input[i] && *input[i] != '\"')
			i++;
		if (*input[i] == '\"')
		{
			token->chr = ft_strdupn(*input, i);
			token->type = DQUOTE;
		}
	}
	if (token->chr != NULL)
		token = new_token(token);
}