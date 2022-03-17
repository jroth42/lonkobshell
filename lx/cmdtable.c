// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   cmdtable.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/03/15 14:23:37 by jroth             #+#    #+#             */
// /*   Updated: 2022/03/15 22:19:34 by jroth            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../inc/shell.h"

// t_token	*token_head(t_token *token)
// {
// 	t_token	*tmp;

// 	tmp = token;
// 	while (tmp && tmp->prev)
// 		tmp = tmp->prev;
// 	return (tmp);
// }

// t_table	*init_table()
// {
// 	t_table	*new;

// 	new = malloc(sizeof(t_table));
// 	new->exec = "";
// 	new->args = NULL;
// 	new->re_in = "";
// 	new->re_out = "";
// 	new->prev = NULL;
// 	new->next = NULL;
// 	return (new);
// }

// int get_cmd(t_token *token)
// {
// 	int		i;
// 	t_token	*tmp;

// 	i = 0;
// 	tmp = token_head(token);
// 	while (tmp && tmp->next)
// 	{
// 		if (*tmp->chr == '|')
// 			i++;
// 		tmp = tmp->next;
// 	}
// 	if (i == 0)
// 		return (1);
// 	if (i == 1)
// 		return (2);
// 	if (i == 2)
// 		return (3);
// 	return (i + 1);
// }

// void	print_table(t_table *table)
// {
// 	int	i;

// 	i = 0;
// 	while (table && table->next)
// 	{
// 		if (table->exec)
// 			printf("%s\n", table->exec);
// 		if (table->args)
// 		{
// 			while (table->args[i])
// 				printf("%s\n", table->args[i++]);
// 		}
// 		if (table->re_in)
// 			printf("%s\n", table->re_in);
// 		if (table->re_out)
// 			printf("%s\n", table->re_out);
// 		table = table->next;
// 	}
// }

// t_table *create_table(t_token *token)
// {
// 	t_table	*new;
// 	t_table	*tmp;

// 	int		cmd;
// 	int		i;
// 	new = init_table();
// 	cmd = get_cmd(token);
// 	i = 0;
// 	while (i++ < cmd)
// 	{
// 		new->num = i;
// 		tmp = new;
// 		new->next = init_table();
// 		new = new->next;
// 		new->prev = tmp;
// 	}
// 	while (new && new->prev)
// 		new = new->prev;
// 	fill_table(new, token);
// 	print_table(new);
// 	return (new);
// }
