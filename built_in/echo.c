/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:05:23 by jroth             #+#    #+#             */
/*   Updated: 2022/04/26 23:16:56 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	printf("%s\n", pwd);
	free(pwd);
	g_exit = SUCCESS;
	return (g_exit);
}

void	check_echoflag(char *arg, bool *opt, int *i)
{
	if (!ft_strcmp(arg, "-n"))
	{
		*opt = true;
		(*i)++;
	}
}

void	ft_echo(t_cmd *cmd)
{
	bool	opt;
	int		i;

	opt = false;
	if (get_arr_size(cmd->exec) > 1)
	{
		i = 1;
		check_echoflag(cmd->exec[i], &opt, &i);
		while (cmd->exec[i])
		{
			printf("%s", cmd->exec[i]);
			if (!opt)
				printf(" ");
			i++;
		}
	}
	if (!opt)
		printf("\n");
}
