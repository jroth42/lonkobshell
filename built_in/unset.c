/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 21:08:04 by jroth             #+#    #+#             */
/*   Updated: 2022/04/25 22:01:13 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

static int	unset_error(char *str, int r_value)
{
	t_string	*sb;
	char		*err_msg;

	sb = s_create();
	s_add_str(sb, "unset: '");
	s_add_str(sb, str);
	s_add_str(sb, "': not a valid identifier");
	err_msg = s_get_str(sb);
	s_destroy(sb);
	error_msg(err_msg, r_value);
	myfree(err_msg);
	return (r_value);
}

static bool	check_valid_arg(char *str)
{
	if (!*str || (!ft_isalpha(*str) && *str != '_'))
		return (false);
	str++;
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (false);
		str++;
	}
	return (true);
}

static bool	rm_env_help(char *str, t_env **env, t_env *curr_env, t_env *prev)
{
	char	*tmp;

	tmp = get_var_name(curr_env);
	if (!ft_strcmp(tmp, str) && !ft_strcmp(curr_env->var, prev->var))
	{
		prev = curr_env->next;
		free(curr_env->var);
		free(curr_env);
		*env = prev;
		free(tmp);
		return (false);
	}
	else if (!ft_strcmp(tmp, str))
	{
		prev->next = curr_env->next;
		free(curr_env->var);
		free(curr_env);
		free(tmp);
		curr_env = NULL;
		return (false);
	}
	return (true);
}

static void	rm_env_var(char *str, t_env **env, t_env *curr_env, t_env *prev)
{
	if (check_valid_arg(str))
	{
		while (curr_env)
		{
			if (!rm_env_help(str, env, curr_env, prev))
				break ;
			prev = curr_env;
			curr_env = curr_env->next;
		}
	}
	else
		g_exit = unset_error(str, FAIL);
}

void	ft_unset(t_cmd *cmd)
{
	t_env	**curr_env;
	int		i;

	g_exit = 0;
	if (get_arr_size(cmd->exec) == 0)
		return ;
	if (!(**cmd->exec))
	{
		g_exit = error_msg("unset: not a valid identifier", FAIL);
		return ;
	}
	i = 0;
	curr_env = get_env(NULL);
	while (cmd->exec[i])
	{
		rm_env_var(cmd->exec[i], curr_env, *curr_env, *curr_env);
		i++;
	}
}
