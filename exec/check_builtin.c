/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:26:37 by jroth             #+#    #+#             */
/*   Updated: 2022/04/18 16:57:01 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

int	ft_strcmp_upper_lower(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*new1;
	unsigned char	*new2;

	i = 0;
	new1 = (unsigned char *)s1;
	new2 = (unsigned char *)s2;
	while (new1[i] && new2[i] && ((new1[i] - new2[i] == 0)
			|| (new1[i] - new2[i] == 32)
			|| (new1[i] - new2[i] == -32)))
		i++;
	if (!new1[i] && new2[i])
		return (-1);
	else if (new1[i] && !new2[i])
		return (1);
	else if (!new1[i] && !new2[i])
		return (0);
	else
		return (new1[i] - new2[i]);
}

bool	check_builtin(t_cmd *table)
{
	if (!table->cmd)
		return (false);
	if (!ft_strcmp_upper_lower(table->cmd, "pwd")
		|| !ft_strcmp(table->cmd, "cd")
		|| !ft_strcmp_upper_lower(table->cmd, "echo")
		|| !ft_strcmp(table->cmd, "export")
		|| !ft_strcmp_upper_lower(table->cmd, "env")
		|| !ft_strcmp(table->cmd, "exit")
		|| !ft_strcmp(table->cmd, "unset"))
		return (true);
	return (false);
}

int	built_in_exec(t_cmd *table, char **env)
{
	if (table->cmd)
	{
		// if (!ft_strcmp_upper_lower(table->cmd, "pwd"))
		// 	ft_pwd();
		// if (!ft_strcmp(table->cmd, "cd"))
		// 	ft_cd(table);
		// if (!ft_strcmp_upper_lower(table->cmd, "echo"))
		// 	ft_echo(table);
		// if (!ft_strcmp(table->cmd, "export"))
		// 	ft_export(table);
		if (!ft_strcmp_upper_lower(table->cmd, "env"))
			ft_env(env);
		// if (!ft_strcmp(table->cmd, "exit"))
		// 	ft_exit(table);
		// if (!ft_strcmp(table->cmd, "unset"))
		// 	ft_unset(table);
		// return (g_exit_status);
		return (0);
	}
	// return (FAIL);
	return (-1);
}

bool	check_single_built_in(t_cmd *tmp, char **env)
{
	if (tmp->prev == NULL && tmp->next == NULL
		&& tmp->re_type == -1 && check_builtin(tmp))
	{
		//g_exit_status = 
		built_in_exec(tmp, env);
		return (true);
	}
	return (false);
}