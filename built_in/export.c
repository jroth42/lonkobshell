/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:59:18 by jroth             #+#    #+#             */
/*   Updated: 2022/04/25 15:20:59 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

static int	export_error(char *str, int r_value)
{
	t_string	*sb;
	char		*err_msg;

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
