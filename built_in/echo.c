/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:05:23 by jroth             #+#    #+#             */
/*   Updated: 2022/04/24 20:25:00 by jroth            ###   ########.fr       */
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
	myfree(pwd);
	g_exit = SUCCESS;
	return (g_exit);
}

static bool	check_valid_opt(char *opt)
{
	int	i;

	i = 0;
	if (ft_strncmp(opt, "-n", 2))
		return (false);
	i += 2;
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static int	skip_valid_opt(char **args, bool *opt)
{
	int	i;

	i = 0;
	if (!check_valid_opt(args[i]))
		return (i);
	*opt = true;
	i++;
	while (args[i])
	{
		if (!check_valid_opt(args[i]) && ft_strcmp(args[i], ""))
			break ;
		i++;
	}
	return (i);
}

void	ft_echo(t_cmd *cmd)
{
	bool	opt;
	int		i;

	opt = false;
	if (get_arr_size(cmd->exec) > 0)
	{
		i = skip_valid_opt(cmd->exec, &opt);
        if (i == 0)
            i = 1;
		while (cmd->exec[i])
		{
			if (ft_strlen(cmd->exec[i]))
				printf("%s", cmd->exec[i]);
			if (ft_strcmp(cmd->exec[i], "")
				&& cmd->exec[i + 1]
				&& ft_strcmp(cmd->exec[i + 1], ""))
				printf(" ");
			i++;
		}
	}
	if (!opt)
		printf("\n");
}
