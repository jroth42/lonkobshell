/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 23:40:10 by hngo              #+#    #+#             */
/*   Updated: 2022/04/18 17:03:13 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

t_env	*last_node(t_env *node)
{
	t_env *tmp;

	tmp = node;
	while (tmp)
	{
		if (tmp && !tmp->next)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

t_env	*env_new(char *env_str)
{
	t_env *new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->str = NULL;
	new->str = ft_strdup(env_str);
	new->next = NULL;
	return (new);
}

void	env_add_back(t_env **list, char *str)
{
	t_env *tmp;

	tmp = NULL;
	if (*list == NULL)
		*list = env_new(str);
	else
	{
		tmp = last_node(*list);
		tmp->next = env_new(str);
	}
}

void	create_env_list(t_env **env_list, char **environ)
{
	int i;

	i = 0;
	while (environ[i])
		env_add_back(env_list, environ[i++]);
}

void	print_env(t_env *ori)
{
	t_env *node;

	node = ori;

	while (node)
	{
		printf("%s\n", node->str);
		node = node->next;
	}
}

void    ft_env(char **env)
{
    t_env *env_struct;

    env_struct = NULL;
    create_env_list(&env_struct, env);
    print_env(env_struct);
}