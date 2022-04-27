/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:36:38 by jroth             #+#    #+#             */
/*   Updated: 2022/04/27 18:46:23 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

void	here_doc_print(t_exec *fds)
{
	while (fds->cmd_count)
	{
		write(0, "> ", 2);
		fds->cmd_count--;
	}
	write(0, "> ", 2);
}

char	*get_word_envname(char **tmp)
{
	t_string	*sb;
	char		*env_name;
	int			i;

	i = 0;
	sb = s_create();
	while (ft_isalnum((*tmp)[i]) || (*tmp)[i] == '_')
		i++;
	s_add_strn(sb, *tmp, i);
	env_name = s_get_str(sb);
	s_destroy(sb);
	*tmp += i;
	return (env_name);
}

void	dollar_expand(t_string **sb, char **tmp)
{
	char	*env_name;

	(*tmp)++;
	if (ft_isalpha(**tmp) || **tmp == '_')
	{
		env_name = get_word_envname(tmp);
		s_add_str(*sb, env_var_value(env_name));
		free(env_name);
	}
	else
		dollar_special_expand(sb, tmp);
}

void	dquote_expand(t_string **sb, char **tmp)
{
	s_add_c(*sb, **tmp);
	(*tmp)++;
	while (**tmp && **tmp != DQUOTE)
	{
		if (**tmp == '$' && (*(*tmp + 1) == DQUOTE || *(*tmp + 1) == ' '))
			s_add_c(*sb, '$');
		else if (**tmp == '$')
		{
			dollar_expand(sb, tmp);
			continue ;
		}
		else
			s_add_c(*sb, **tmp);
		(*tmp)++;
	}
	if (**tmp)
	{
		s_add_c(*sb, **tmp);
		(*tmp)++;
	}
}
