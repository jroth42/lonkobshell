/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:12:28 by jroth             #+#    #+#             */
/*   Updated: 2022/04/25 21:51:42 by jroth            ###   ########.fr       */
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

bool	char_checker(const char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '$')
		return (false);
	return (true);
}

char	*env_var_variable(char **input)
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
