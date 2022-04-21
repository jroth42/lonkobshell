/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:09:19 by jroth             #+#    #+#             */
/*   Updated: 2022/04/21 17:09:19 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

static int	get_env_size(t_env *env)
{
	int	res;

	res = 0;
	env = *(get_env(NULL));
	while (env)
	{
		res++;
		env = env->next;
	}
	return (res);
}

char	**get_env_arr(void)
{
	int		i;
	t_env	*tmp;
	char	**env_arr;

	tmp = *(get_env(NULL));
	env_arr = ft_calloc(get_env_size(tmp) + 1, sizeof(char *));
	i = 0;
	while (tmp)
	{
		env_arr[i] = ft_strdup(tmp->var);
		i++;
		tmp = tmp->next;
	}
	return (env_arr);
}

char	*get_var_name(t_env *env)
{
	t_string		*sb;
	int				i;
	char			*res;

	sb = s_create();
	i = 0;
	while (env->var[i] && env->var[i] != '=')
		i++;
	s_add_strn(sb, env->var, i);
	res = s_get_str(sb);
	s_destroy(sb);
	return (res);
}

char	*env_var_value(char *str)
{
	t_env	*env;
	char	*var_name;

	env = *get_env(NULL);
	while (env)
	{
		var_name = get_var_name(env);
		if (!ft_strcmp(var_name, str))
		{
			free(var_name);
			if (ft_strchr(env->var, '='))
				return (ft_strchr(env->var, '=') + 1);
			else
				return (NULL);
		}
		free(var_name);
		env = env->next;
	}
	return (NULL);
}

void	free_env(void)
{
	t_env	**env;
	t_env	*curr;
	t_env	*next;

	env = get_env(NULL);
	curr = *env;
	while (curr)
	{
		next = curr->next;
		free(curr->var);
		free(curr);
		curr = next;
	}
}
