/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:59:18 by jroth             #+#    #+#             */
/*   Updated: 2022/04/24 21:06:03 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

// UTLS
static char	*get_args_var_name(char *args)
{
	t_string	    *sb;
	int				i;
	char			*res;

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
	t_string	    *sb;
	int				i;

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

//export
static int	export_error(char *str, int r_value)
{
	t_string        *sb;
	char			*err_msg;

	sb = s_create();
	s_add_str(sb, "export: '");
	s_add_str(sb, str);
	s_add_str(sb, "': not a valid identifier");
	err_msg = s_get_str(sb);
	s_destroy(sb);
	error_msg(err_msg, r_value);
	myfree(err_msg);
	return (r_value);
}

static void	add_env_var(t_cmd *table, t_env **env)
{
	t_env	*existing;
	int		i;

	i = 0;
	while (table->exec[i])
	{
		if (check_valid_var(&table->exec[i]))
		{
			existing = check_var_existence(env, table->exec[i]);
			if (!existing)
				append_env(env, new_env(table->exec[i]));
			else
			{
				free(existing->var);
				existing->var = ft_strdup(table->exec[i]);
				if (strchr(existing->var, '='))
					existing->hidden = false;
			}
		}
		else
			g_exit = export_error(table->exec[i], FAIL);
		i++;
	}
}

static void	print_env_vars(t_env *env)
{
	t_env	*tmp;
	int		ascii;

	ascii = 65;
	while (ascii < 123)
	{
		tmp = env;
		while (tmp)
		{
			if (tmp->var[0] == ascii)
				printf("declare -x %s\n", tmp->var);
			tmp = tmp->next;
		}
		ascii++;
	}
}

void	ft_export(t_cmd *cmd)
{
	t_env	**env;

	env = get_env(NULL);
	if (get_arr_size(cmd->exec) == 0)
		print_env_vars(*env);
	else if (!(**cmd->exec))
	{
		g_exit = error_msg("export: not a valid identifier", FAIL);
		return ;
	}
	else
		add_env_var(cmd, env);
}
