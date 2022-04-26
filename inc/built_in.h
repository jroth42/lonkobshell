/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:48:40 by jroth             #+#    #+#             */
/*   Updated: 2022/04/26 03:43:58 by jroth            ###   ########.fr       */
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

void	ft_echo(t_cmd *cmd);
void	ft_exit(t_cmd *cmd);
void	ft_env(void);
int		ft_pwd(void);
void	ft_export(t_cmd *cmd);
void	ft_unset(t_cmd *cmd);
void	ft_cd(t_cmd *cmd);

//export utils
int	ft_strcmp_upper_lower(const char *s1, const char *s2);
bool	check_valid_var(char **str);
t_env	*check_var_existence(t_env **env, char *args);
// env utils
void	free_env(void);
t_env	**get_env(char **environ);
t_env	*append_env(t_env **head, t_env *new);
t_env	*get_last_env(t_env *head);
t_env	*new_env(char *str);
char	**get_env_arr(void);
char	*get_var_name(t_env *env);
char	*env_var_value(char *str);

#endif
