/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:26:37 by jroth             #+#    #+#             */
/*   Updated: 2022/04/24 21:31:51 by jroth            ###   ########.fr       */
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

bool	check_builtin(t_cmd *cmd)
{
	if (!cmd->cmd)
		return (false);
	if (!ft_strcmp_upper_lower(cmd->cmd, "pwd")
		|| !ft_strcmp(cmd->cmd, "cd")
		|| !ft_strcmp_upper_lower(cmd->cmd, "echo")
		|| !ft_strcmp(cmd->cmd, "export")
		|| !ft_strcmp_upper_lower(cmd->cmd, "env")
		|| !ft_strcmp(cmd->cmd, "exit")
		|| !ft_strcmp(cmd->cmd, "unset"))
		return (true);
	return (false);
}

int	built_in_exec(t_cmd *cmd)
{
	if (cmd->cmd)
	{
		if (!ft_strcmp_upper_lower(cmd->cmd, "pwd"))
			ft_pwd();
		// if (!ft_strcmp(cmd->cmd, "cd"))
		// 	ft_cd(cmd);
		if (!ft_strcmp_upper_lower(cmd->cmd, "echo"))
			ft_echo(cmd);
		if (!ft_strcmp(cmd->cmd, "export"))
			ft_export(cmd);
		if (!ft_strcmp_upper_lower(cmd->cmd, "env"))
			ft_env();
		if (!ft_strcmp(cmd->cmd, "exit"))
			ft_exit(cmd);
		if (!ft_strcmp(cmd->cmd, "unset"))
			ft_unset(cmd);
		// return (g_exit);
		return (SUCCESS);
	}
	return (FAIL);
}

bool	check_single_built_in(t_cmd *tmp)
{
	if (tmp->prev == NULL && tmp->next == NULL
		&& check_builtin(tmp))
	{
		g_exit = built_in_exec(tmp);
		return (true);
	}
	return (false);
}