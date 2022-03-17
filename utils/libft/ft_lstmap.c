/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:09:49 by jroth             #+#    #+#             */
/*   Updated: 2021/09/16 20:09:36 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*f_list;
	t_list	*f_el;

	if (!lst || !f)
		return (0);
	f_list = NULL;
	while (lst != NULL)
	{
		f_el = ft_lstnew((f)(lst->content));
		if (f_el == NULL)
		{
			ft_lstclear(&f_list, (*del));
			free(f_list);
			return (NULL);
		}
		ft_lstadd_back(&f_list, f_el);
		lst = lst->next;
	}
	return (f_list);
}
