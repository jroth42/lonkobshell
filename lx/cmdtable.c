// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   cmdcmd.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/03/15 14:23:37 by jroth             #+#    #+#             */
// /*   Updated: 2022/03/15 22:19:34 by jroth            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../inc/shell.h"

//	return empty cmd struct
t_cmd	*create_cmd(t_cmd *cmd)
{
	t_cmd *new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->exec = NULL;
	new->args = NULL;
	new->re_in = NULL;
	new->re_out = NULL;
	new->fd_in = STDIN;
	new->fd_out = STDOUT;
	new->next = NULL;
	if (!cmd)
	{
		new->prev = NULL;
		return (new);
	}
	else
	{
		new->prev = cmd;
		cmd->next = new;
	}
	return (new);
}

//	strjoin args from tokenlist
void	fill_arguments(t_token *token, t_cmd **cmd)
{
	char	*join;
	char	*copy;

	copy = NULL;
	join = NULL;
	if ((*cmd)->args)
	{
		join = ft_strjoin((*cmd)->args, " ");
		copy = join;
		join = ft_strjoin(copy, token->chr);
		(*cmd)->args = join;
	}
	else
		(*cmd)->args = ft_strdup(token->chr);
}

//	walk through tokens and append them to cmdcmd struct
void	command_cmd(t_node *node)
{
	t_token	*tmp;

	tmp = node->token;
	while (tmp && tmp->prev)
		tmp = tmp->prev;
	node->cmd = create_cmd(NULL);
	while (tmp->next)
	{
		if (tmp->type == COMMAND)
			(node)->cmd->exec = ft_strdup(tmp->chr);
		if (tmp->type == ARG || tmp->type == SQUOTE || tmp->type == DQUOTE)
			fill_arguments(tmp, &node->cmd);
		if (tmp->type == GREAT || tmp->type == GREATGREAT)
			(node)->cmd->re_out = ft_strdup(tmp->chr);
		if (tmp->type == LESS || tmp->type == LESSLESS)
			(node)->cmd->re_in = ft_strdup(tmp->chr);
		if (tmp->type == PIPE)
		{
			(node)->cmd->next = create_cmd(node->cmd);
			node->cmd = node->cmd->next;
		}
		tmp = tmp->next;
	}
}


// void	fill_arguments(t_token **token, t_cmd **cmd)
// {
// 	t_token	*tmp;
// 	int i;
// 	char	**args;

// 	tmp = *token;
// 	i = 0;
// 	while (tmp && tmp->next)
// 	{
// 		if (tmp->type == ARG)
// 			i++;
// 		tmp = tmp->next;
// 	}
// 	if (i > 0)
// 	{
// 		args = malloc(sizeof(char **) * (i + 1));
// 		tmp = *token;
// 		i = 0;
// 		while (tmp && tmp->next && tmp->type != PIPE)
// 		{
// 			if (tmp->type == ARG)
// 				args[i++] = tmp->chr;
// 			tmp = tmp->next;
// 		}
// 		args[i] = NULL;
// 		if (tmp->next)
// 			(*token) = tmp->next;
// 		(*cmd)->args = args;
// 	}
// }