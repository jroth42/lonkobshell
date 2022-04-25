/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:51:06 by jroth             #+#    #+#             */
/*   Updated: 2022/04/25 14:51:06 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

static void	export_cd(char *args)
{
	t_env	**env;
	t_env	*existing;

	env = get_env(NULL);
	existing = check_var_existence(env, args);
	if (!existing)
		append_env(env, new_env(args));
	else
	{
		myfree(existing->var);
		existing->var = ft_strdup(args);
	}
}

static int	cd_error(char *str, int r_value)
{
	t_string	*sb;
	char		*err_msg;

	sb = s_create();
	s_add_str(sb, "cd: ");
	s_add_str(sb, str);
	s_add_str(sb, ": No such file or directory");
	err_msg = s_get_str(sb);
	s_destroy(sb);
	error_msg(err_msg, r_value);
	myfree(err_msg);
	return (r_value);
}

static void	change_pwd_var(void)
{
	t_string	*sb;
	char		*tmp;
	char		*tmp_pwd;

	sb = s_create();
	s_add_str(sb, "OLDPWD=");
	s_add_str(sb, env_var_value("PWD"));
	tmp = s_get_str(sb);
	export_cd(tmp);
	s_reset(sb);
	s_add_str(sb, "PWD=");
	tmp_pwd = getcwd(NULL, 0);
	s_add_str(sb, tmp_pwd);
	free(tmp);
	free(tmp_pwd);
	tmp = s_get_str(sb);
	export_cd(tmp);
	s_destroy(sb);
	free(tmp);
}

static char	*get_home_dir(void)
{
	t_env	*curr_env;

	curr_env = *(get_env(NULL));
	while (curr_env)
	{
		if (!ft_strncmp(curr_env->var, "HOME", 4))
			return (ft_strchr(curr_env->var, '/'));
		curr_env = curr_env->next;
	}
	return (NULL);
}

void	ft_cd(t_cmd *cmd)
{
	cmd->exec++;
	if (!(*cmd->exec) || !ft_strcmp(*cmd->exec, "~")
		|| !ft_strcmp(*cmd->exec, "--"))
	{
		if (*cmd->exec)
			myfree(*cmd->exec);
		*cmd->exec = ft_strdup(get_home_dir());
	}
	else if (!ft_strcmp(*cmd->exec, "-"))
	{
		myfree(*cmd->exec);
		*cmd->exec = ft_strdup(env_var_value("OLDPWD"));
		printf("%s\n", *cmd->exec);
	}
	if (chdir(*cmd->exec) == -1)
	{
		g_exit = cd_error(*cmd->exec, FAIL);
		return ;
	}
	change_pwd_var();
}
