/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:48:40 by jroth             #+#    #+#             */
/*   Updated: 2022/04/21 18:47:55 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

typedef struct s_env
{
	char			*var;
	bool			hidden;
	struct s_env	*next;
}			t_env;

// env
t_env	**get_env(char **environ);
void	ft_env(void);
t_env	*append_env(t_env **head, t_env *new);
t_env	*get_last_env(t_env *head);
t_env	*new_env(char *str);
char	**get_env_arr(void);
char	*get_var_name(t_env *env);
char	*env_var_value(char *str);
#endif
