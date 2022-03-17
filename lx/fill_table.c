// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   fill_table.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/03/15 21:05:33 by jroth             #+#    #+#             */
// /*   Updated: 2022/03/15 23:19:08 by jroth            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../inc/shell.h"

// void	fill_commands(t_table *table, t_token *token)
// {
// 	t_token	*tmp;
// 	t_table	*table_tmp;

// 	table_tmp = table;
// 	tmp = token;
// 	while (table_tmp && table_tmp->next)
// 	{
// 		if (tmp->type == COMMAND && tmp->used == false)
// 		{
// 			table_tmp->exec = tmp->chr;
// 			tmp->used = true;
// 			table_tmp = table_tmp->next;
// 		}
// 		tmp = tmp->next;
// 	}
// }

// int	count_args(t_token *token)
// {
// 	t_token	*tmp;
// 	int		i;

// 	i = 0;
// 	tmp = token;
// 	while (tmp && tmp->next)
// 	{
// 		if (tmp->type == ARG || tmp->type == OPTION)
// 			i++;
// 		tmp = tmp->next;
// 	}
// 	return (i);
// }

// // void	fill_args(t_table *table, t_token *token)
// // {
// // 	t_token	*tmp;
// // 	t_table	*table_tmp;
// // 	int		i;

// // 	i = 0;
// // 	table_tmp = table;
// // 	tmp = token;
// // 	table->args = malloc(sizeof(char *) * (count_args(token) + 1));
// // 	while (table_tmp && table_tmp->next)
// // 	{
// // 		if (tmp->type == ARG || tmp->type == OPTION)
// // 		{
// // 			table->args[i] = ft_strdup(tmp->chr);
// // 			tmp = tmp->next;
// // 			i++;
// // 		}
// // 		if (tmp->type == '|')
// // 			table_tmp = table_tmp->next;
// // 		tmp = tmp->next;
// // 	}
// // }

// void	redirects(t_table *table, t_token *token)
// {
// 	t_token	*tmp;
// 	t_table	*table_tmp;

// 	table_tmp = table;
// 	tmp = token;
// 	while (table_tmp && table_tmp->next)
// 	{
// 		if (tmp->type == ARG && tmp->prev->type == LESS)
// 			table_tmp->re_out = ft_strjoin("<", tmp->chr);
// 		if (tmp->type == ARG && tmp->prev->type == LESSLESS)
// 			table_tmp->re_out = ft_strjoin("<<", tmp->chr);
// 		if (tmp->type == ARG && tmp->next->type == GREAT)
// 			table_tmp->re_in = ft_strjoin(tmp->chr, ">");
// 		if (tmp->type == ARG && tmp->next->type == GREATGREAT)
// 			table_tmp->re_in = ft_strjoin(tmp->chr, ">>");
// 		if (tmp->type == PIPE)
// 			table_tmp = table_tmp->next;
// 		tmp = tmp->next;
// 	}	
// }

// void	fill_table(t_table *table, t_token *token)
// {
// 	t_token	*tmp;
// 	t_table	*table_tmp;

// 	table_tmp = table;
// 	tmp = token_head(token);
// 	// redirects(table_tmp, tmp);
// 	fill_commands(table_tmp, tmp);
// 	// fill_args(table_tmp, tmp);
// }
