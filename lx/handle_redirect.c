/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:24:01 by jroth             #+#    #+#             */
/*   Updated: 2022/03/19 18:29:40 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

void	handle_redirect_out(t_token **token, char **input)
{
	if (*(*input + 1) == '>')
	{
		(*token)->prev->type = GREATGREAT;	
		(*input) += 2;
	}
	else
	{
		(*token)->prev->type = GREAT;
		(*input) += 1;
	}
}

char	*find_filename_right(char **input)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = *input;
	if (str && str[i] == '<')
	{
		while (str[i] == '<')
			i++;
		while (str[i] && whitespace(str[i]))
			i++;
		while (str[i + j] && !whitespace(str[i + j]))
			j++;
	}
	(*input) += (i + j);
	str = ft_strdupn(str + i, j);
	return (str);
}

void	handle_redirect_in(t_token **token, char **input)
{
	if (*(*input + 1) == '<')
	{
		(*token)->chr = find_filename_right(input);
		(*token)->type = LESSLESS;
	}		
	else
	{
		(*token)->chr = find_filename_right(input);
		(*token)->type = LESS;
	}
	if ((*token)->chr)
		*token = create_token(*token);
}

void	handle_redirections(t_token **token, char  **input)
{
	if (**input == '<')
		handle_redirect_in(token, input);
	if (**input == '>')
		handle_redirect_out(token, input);
}
