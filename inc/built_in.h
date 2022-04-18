/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hngo <hngo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:48:40 by jroth             #+#    #+#             */
/*   Updated: 2022/04/18 21:57:26 by hngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

typedef struct s_env
{
	char			*str;
	int				flag;
	struct s_env	*next;
}					t_env;

//env_struct
void	print_env(t_env *ori);
void	create_env_list(t_env **env_list, char **environ);
void	env_add_back(t_env **list, char *str);
t_env	*env_new(char *env_str);
t_env	*last_node(t_env *node);





void    ft_env(char **env);
void	ft_export(t_cmd *table, t_env *env_struct);
void    unset_env(t_env **head);
void    modify_env(t_env **node, char *str, int mode);
int 	is_env(t_env *node, char *str);
int 	compare_env(char *env_str, char *str, int mode);
int 	len_til_equal(char *str);
int 	has_equal(char *str);

#endif
