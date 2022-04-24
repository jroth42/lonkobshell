/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:12:28 by jroth             #+#    #+#             */
/*   Updated: 2022/04/24 23:52:36 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

static bool	check_expand_arg(char **input)
{
	if (ft_strchr(*input, '$')
		|| ft_strchr(*input, '\'')
		|| ft_strchr(*input, '\"'))
		return (true);
	return (false);
}

static void	dollar_special_expand(t_string **t_str, char **input)
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

bool	char_checker(const char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '$')
		return (false);
	return (true);
}

static char	*env_var_variable(char **input)
{
	t_string		*t_str;
	char			*env_name;
	int				i;
	int				j;

	i = 0;
	j = 0;
	t_str = s_create();
	while (ft_isdigit((*input)[i]) || (*input)[i] == '_')
		i++;
	while (!white_space((*input)[i + j]) && (*input)[i + j]
		&& char_checker((*input)[i + j]))
		j++;
	s_add_strn(t_str, *input, j);
	env_name = s_get_str(t_str);
	s_destroy(t_str);
	*input += i + j;
	return (env_name);
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
		dollar_special_expand(t_str, input); // FIX ME
	if ((*token)->prev)
		(*token)->type = DOLLAR;
	else
		(*token)->type = COMMAND;
}


void	dquote(t_token **token, t_string **t_str, char **input)
{
	s_add_c(*t_str, **input);
	(*input)++;
	while (**input && **input != DQUOTE)
	{
		if (**input == '$' && (*(*input + 1) == DQUOTE || *(*input + 1) == ' '))
			s_add_c(*t_str, '$');
		else if (**input == '$')
		{
			expand_var(token, t_str, input);
			continue ;
		}
		else
			s_add_c(*t_str, **input);
		(*input)++;
	}
	if (**input)
	{
		s_add_c(*t_str, **input);
		(*input)++;
	}
	if ((*token)->prev)
		(*token)->type = DQUOTE;
	else
		(*token)->type = COMMAND;
}

void	squote(t_token **token, t_string **t_str, char **input)
{
	int	i;

	i = 1;
	while ((*input)[i] && (*input)[i] != SQUOTE)
		i++;
	if ((*input)[i] == SQUOTE)
		i++;
	s_add_strn(*t_str, *input, i);
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
	s_destroy(t_str);
}


int	expander(t_token **token, char **input)
{
	if (*token)
	{
		if (check_expand_arg(input))
		{
			expand(token, input);
			if (!ft_strcmp((*token)->chr, "\"\"") || !(*token)->chr)
				(*token)->type = -5;
		}
	}
	*token = create_token(*token);
	return (1);
}
