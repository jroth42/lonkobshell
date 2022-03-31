/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:24:01 by jroth             #+#    #+#             */
/*   Updated: 2022/03/31 19:18:06 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

//	lil helper function
bool	check_char(const char c)
{
	if (c == '>' || c == '<')
		return (true);
	return (false);
}

//	finds and returns the next word after the redirection operator
char	*find_filename(char **input)
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
		while (str[i] && whitespace(str[i]))
			i++;
		while (str[i + j] && !whitespace(str[i + j]))
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
void	handle_redirect_out(t_token **token, char **input)
{
	char	*join;

	if (*(*input + 1) == '>')
	{
		join = find_filename(input);
		// (*token)->chr = ft_strjoin(">>", join);
		(*token)->chr = ft_strdup(join);
		(*token)->type = GREATGREAT;
	}		
	else
	{
		join = find_filename(input);
		// (*token)->chr = ft_strjoin(">", join);
		(*token)->chr = ft_strdup(join);
		(*token)->type = GREAT;
	}
	if ((*token)->chr)
		*token = create_token(*token);
}

//	checks if << or < before assigning token
void	handle_redirect_in(t_token **token, char **input)
{
	char	*join;

	if (*(*input + 1) == '<')
	{
		join = find_filename(input);
		// (*token)->chr = ft_strjoin("<<", join);
		(*token)->chr = ft_strdup(join);
		(*token)->type = LESSLESS;
	}		
	else
	{
		join = find_filename(input);
		// (*token)->chr = ft_strjoin("<", join);
		(*token)->chr = ft_strdup(join);
		(*token)->type = LESS;
	}
	if ((*token)->chr)
		*token = create_token(*token);
}

//	redirect call from lexer
void	handle_redirections(t_token **token, char **input)
{
	if (**input == '<')
		handle_redirect_in(token, input);
	if (**input == '>')
		handle_redirect_out(token, input);
}
