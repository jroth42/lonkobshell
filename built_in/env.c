/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:04:16 by jroth             #+#    #+#             */
/*   Updated: 2022/04/21 17:04:16 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

t_env	*new_env(char *str)
{
	t_env	*new;

	if (!str)
		return (NULL);
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->var = ft_strdup(str);
	if (ft_strchr(str, '='))
		new->hidden = false;
	else
		new->hidden = true;
	new->next = NULL;
	return (new);
}

t_env	*get_last_env(t_env *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

t_env	*append_env(t_env **head, t_env *new)
{
	t_env	*last;

	if (!(*head))
		*head = new;
	else
	{
		last = get_last_env(*head);
		last->next = new;
	}
	return (new);
}

t_env	**get_env(char **environ)
{
	static t_env	*env;
	int				i;

	if (!env)
	{
		i = 0;
		while (environ[i])
		{
			append_env(&env, new_env(environ[i]));
			i++;
		}
	}
	return (&env);
}

void	ft_env(void)
{
	t_env	*tmp;

	tmp = *(get_env(NULL));
	while (tmp)
	{
		if (!tmp->hidden)
			printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
}
