/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hngo <hngo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 23:40:10 by hngo              #+#    #+#             */
/*   Updated: 2022/04/06 16:52:29 by hngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return 0;
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char		*s2;
	int			i;
	int			len;

	len = ft_strlen(s1);
	s2 = malloc(sizeof(char) * (len + 1));
	if (s2 == NULL)
		return ((char *) NULL);
	i = 0;
	while (i < len)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

t_envbuilt	*last_node(t_envbuilt *node)
{
	t_envbuilt *tmp;

	tmp = node;
	while (tmp)
	{
		if (tmp && !tmp->next)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

t_envbuilt	*env_new(char *env_str)
{
	t_envbuilt *new;

	new = (t_envbuilt *)malloc(sizeof(t_envbuilt));
	if (!new)
		return (NULL);
	new->str = NULL;
	new->str = ft_strdup(env_str);
	new->next = NULL;
	return (new);
}

void	env_add_back(t_envbuilt **list, char *str)
{
	t_envbuilt *tmp;

	tmp = NULL;
	if (*list == NULL)
		*list = env_new(str);
	else
	{
		tmp = last_node(*list);
		tmp->next = env_new(str);
	}
}

void	create_env_list(t_envbuilt **env_list, char **environ)
{
	int i;

	i = 0;
	while (environ[i])
	{
		env_add_back(env_list, environ[i]);
		i++;
	}
}

void	print_nodes(t_envbuilt *ori)
{
	t_envbuilt *node;

	node = ori;
	int i;

	i = 0;
	while (node)
	{
		printf("%s\n", node->str);
		node = node->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_envbuilt *env_struct;

	env_struct = NULL;
	
	create_env_list(&env_struct, envp);
	print_nodes(env_struct);
	return 0;
}