/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:14:03 by jroth             #+#    #+#             */
/*   Updated: 2022/04/25 15:23:15 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

static void	valid_exit(void)
{
	write(2, "exit\n", 5);
	free_env();
	exit(g_exit);
}

static int	exit_error(char *str, int r_value)
{
	t_string	*sb;
	char		*err_msg;

	sb = s_create();
	s_add_str(sb, "exit: ");
	s_add_str(sb, str);
	s_add_str(sb, ": numeric argument required");
	err_msg = s_get_str(sb);
	s_destroy(sb);
	error_msg(err_msg, r_value);
	myfree(err_msg);
	return (r_value);
}

static bool	check_valid_arg(char *arg)
{
	if (!*arg || (*arg != '+' && *arg != '-' && !ft_isdigit(*arg)))
		return (false);
	arg++;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (false);
		arg++;
	}
	return (true);
}

void	ft_exit(t_cmd *cmd)
{
	if (!ft_strcmp(*cmd->exec, "exit"))
	{
		(cmd->exec)++;
		if (get_arr_size(cmd->exec) > 0)
		{
			if (ft_isalpha(**cmd->exec)
				|| get_arr_size(cmd->exec) == 1)
			{
				if (check_valid_arg(*cmd->exec))
					g_exit = ft_atoi(*cmd->exec);
				else
					g_exit = exit_error(*cmd->exec, 255);
				// free_table(&cmd);
				valid_exit();
			}
			g_exit = error_msg("exit: too many arguments", FAIL);
			return ;
		}
		g_exit = SUCCESS;
		// free_table(&cmd);
		valid_exit();
	}
}