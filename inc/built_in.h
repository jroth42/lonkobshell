/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:48:40 by jroth             #+#    #+#             */
/*   Updated: 2022/04/18 17:08:28 by jroth            ###   ########.fr       */
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

// env
void    ft_env(char **env);

#endif
