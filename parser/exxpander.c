/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exxpander.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 21:50:24 by jroth             #+#    #+#             */
/*   Updated: 2022/04/27 18:51:05 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

void	dollar_special_expand(t_string **t_str, char **input)
{
	if (**input == '$')
	{
		s_add_str(*t_str, "$$");
		(*input)++;
	}
	else if (**input == '?')
	{
		s_add_int(*t_str, g_exit);
		(*input)++;
	}
	else if (ft_isdigit(**input))
		(*input)++;
	else if (!(**input) || (**input) == ' ')
	{
		s_add_c((*t_str), '$');
		(*input)++;
	}
}

void	expand_var(t_token **token, t_string **t_str, char **input)
{
	char	*var;

	(*input)++;
	if (ft_isalpha(**input) || **input == '_')
	{
		var = env_var_variable(input);
		s_add_str(*t_str, env_var_value(var));
		free(var);
	}
	else
		dollar_special_expand(t_str, input);
	if ((*token)->prev)
		(*token)->type = DOLLAR;
	else
		(*token)->type = COMMAND;
}

void	dquote(t_token **token, t_string **t_str, char **input)
{
	int	i;

	i = 1;
	while ((*input)[i] && (*input)[i] != DQUOTE)
		i++;
	if ((*input)[i] == DQUOTE)
		i++;
	s_add_strn(*t_str, *input + 1, i - 2);
	(*token)->type = DQUOTE;
	*input += i;
}

void	squote(t_token **token, t_string **t_str, char **input)
{
	int	i;

	i = 1;
	while ((*input)[i] && (*input)[i] != SQUOTE)
		i++;
	if ((*input)[i] == SQUOTE)
		i++;
	s_add_strn(*t_str, *input + 1, i - 2);
	(*token)->type = SQUOTE;
	*input += i;
}

void	expand(t_token **token, char **input)
{
	t_string	*t_str;

	t_str = s_create();
	{
		if (**(input) == '$')
			expand_var(token, &t_str, input);
		else if (**input == '\"')
			dquote(token, &t_str, input);
		else if (**input == '\'')
			squote(token, &t_str, input);
	}
	if ((*token)->chr)
		myfree((*token)->chr);
	(*token)->chr = s_get_str(t_str);
	if (!(*token)->prev || (*token)->prev->type == PIPE)
		(*token)->type = COMMAND;
	s_destroy(t_str);
}
