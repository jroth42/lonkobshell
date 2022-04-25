/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:16:43 by jroth             #+#    #+#             */
/*   Updated: 2022/04/25 15:20:49 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

static char	*get_args_var_name(char *args)
{
	t_string	*sb;
	int			i;
	char		*res;

	sb = s_create();
	i = 0;
	while (args[i])
	{
		if (args[i] == '=')
			break ;
		i++;
	}
	s_add_strn(sb, args, i);
	res = s_get_str(sb);
	s_destroy(sb);
	return (res);
}

t_env	*check_var_existence(t_env **env, char *args)
{
	t_env	*tmp;
	char	*var_name;
	char	*args_var_name;

	tmp = *env;
	while (tmp)
	{
		var_name = get_var_name(tmp);
		args_var_name = get_args_var_name(args);
		if (!ft_strcmp(var_name, args_var_name))
		{
			myfree(args_var_name);
			myfree(var_name);
			return (tmp);
		}
		myfree(args_var_name);
		myfree(var_name);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	rm_pluschar(char **str)
{
	t_string	*sb;
	int			i;

	sb = s_create();
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '+')
		{
			i++;
			continue ;
		}
		s_add_c(sb, (*str)[i]);
		i++;
	}
	free(*str);
	*str = s_get_str(sb);
	s_destroy(sb);
}

bool	check_valid_var(char **str)
{
	int		i;
	bool	rm_plus;

	rm_plus = false;
	if (!ft_isalpha(**str) && **str != '_')
		return (false);
	i = 1;
	while ((*str)[i] && (*str)[i] != '=')
	{
		if ((*str)[i] == '+' && (*str)[i + 1] && (*str)[i + 1] == '=')
		{
			i++;
			rm_plus = true;
			continue ;
		}
		if (!ft_isalnum((*str)[i]) && (*str)[i] != '_')
			return (false);
		i++;
	}
	if (rm_plus)
		rm_pluschar(str);
	return (true);
}
