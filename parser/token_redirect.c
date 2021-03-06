/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:24:01 by jroth             #+#    #+#             */
/*   Updated: 2022/04/27 18:21:25 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

//	lil helper function
static bool	check_char(const char c)
{
	if (c == '>' || c == '<')
		return (true);
	return (false);
}

//	finds and returns the next word after the redirection operator
static char	*find_filename(char **input)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = *input;
	if (str && check_char(str[i]))
	{
		while (check_char(str[i]))
			i++;
		while (white_space(str[i]))
			i++;
		while (str[i + j] && !white_space(str[i + j]))
		{
			j++;
			if (check_char(str[i + j]))
				break ;
		}
	}
	(*input) += (i + j);
	return (ft_strdupn(str + i, j));
}

//	checks if >> or > before assigning token
static void	handle_redirect_out(t_token **token, char **input)
{
	char	*join;

	if (*(*input + 1) == '>')
	{
		join = find_filename(input);
		(*token)->chr = ft_strdup(join);
		(*token)->type = APPEND;
	}		
	else
	{
		join = find_filename(input);
		(*token)->chr = ft_strdup(join);
		(*token)->type = TRUNCATE;
	}
	if (!ft_strcmp(join, ""))
	{
		(*token)->chr = ft_strdup(">");
		(*token)->type = -5;
	}
	if ((*token)->chr)
		*token = create_token(*token);
	if (join)
		myfree(join);
}

//	checks if << or < before assigning token
static void	handle_redirect_in(t_token **token, char **input)
{
	char	*join;

	if (*(*input + 1) == '<')
	{
		join = find_filename(input);
		(*token)->chr = ft_strdup(join);
		(*token)->type = HEREDOC;
	}		
	else
	{
		join = find_filename(input);
		(*token)->chr = ft_strdup(join);
		(*token)->type = READ_INPUT;
	}
	if (!ft_strcmp(join, ""))
	{
		(*token)->chr = ft_strdup("<");
		(*token)->type = -5;
	}
	if ((*token)->chr)
		*token = create_token(*token);
	if (join)
		myfree(join);
}

//	redirect call from lexer
void	handle_redirections(t_token **token, char **input)
{
	if (**input == '<')
		handle_redirect_in(token, input);
	if (**input == '>')
		handle_redirect_out(token, input);
}
