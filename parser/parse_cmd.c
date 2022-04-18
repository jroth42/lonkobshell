/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:23:37 by jroth             #+#    #+#             */
/*   Updated: 2022/03/15 22:19:34 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

//	return empty cmd struct
t_cmd	*create_cmd(t_cmd *cmd)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->exec = NULL;
	new->args = NULL;
	new->re_in = NULL;
	new->re_out = NULL;
	new->re_type = -1;
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

//	create 2D array of arguments
void	parse_args(t_cmd **cmd)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_split((*cmd)->args, ' ');
	while (args[i])
		i++;
	(*cmd)->exec = malloc(sizeof(char **) * (i + 2));
	if (!(*cmd)->exec)
		return ;
	(*cmd)->exec[0] = ft_strdup((*cmd)->cmd);
	i = 0;
	while (args[i++])
		(*cmd)->exec[i] = ft_strdup(args[i - 1]);
	(*cmd)->exec[i] = NULL;
}

// create 2D array with exec cmd at [0] if args available parse_args
void	create_exec(t_cmd **cmd)
{
	t_cmd	*head;

	while ((*cmd) && (*cmd)->prev)
		(*cmd) = (*cmd)->prev;
	head = *cmd;
	while ((*cmd))
	{
		if ((*cmd)->args && (*cmd)->cmd)
			parse_args(cmd);
		else if ((*cmd)->cmd)
		{
			(*cmd)->exec = malloc(sizeof(char **) * 2);
			(*cmd)->exec[0] = ft_strdup((*cmd)->cmd);
			(*cmd)->exec[1] = NULL;
		}
		*cmd = (*cmd)->next;
	}
	*cmd = head;
}

//	strjoin args from tokenlist
//	later split them up again in parse_args -> create_exec to create **args
void	fill_arguments(t_token *token, t_cmd **cmd)
{
	char	*join;
	char	*copy;

	if ((*cmd)->args)
	{
		copy = ft_strjoin((*cmd)->args, " ");
		join = ft_strjoin(copy, token->chr);
		(*cmd)->args = join;
	}
	else
		(*cmd)->args = ft_strdup(token->chr);
}

//	walk through tokens and append them to cmd struct
//	create new cmd struct if pipe is found
void	parse_cmd(t_node *node)
{
	t_token	*tmp;

	tmp = node->token;
	while (tmp && tmp->prev)
		tmp = tmp->prev;
	node->cmd = create_cmd(NULL);
	while (tmp->next)
	{
		if (tmp->type == COMMAND)
			(node)->cmd->cmd = ft_strdup(tmp->chr);
		if (tmp->type == ARG || tmp->type == SQUOTE
			|| tmp->type == DQUOTE)
			fill_arguments(tmp, &node->cmd);
		if (tmp->type == GREAT || tmp->type == GREATGREAT)
		{
			(node)->cmd->re_out = ft_strdup(tmp->chr);
			(node)->cmd->re_type = tmp->type;
		}
		if (tmp->type == LESS || tmp->type == LESSLESS)
		{
			(node)->cmd->re_in = ft_strdup(tmp->chr);
			(node)->cmd->re_type = tmp->type;
		}
		if (tmp->type == PIPE)
		{
			(node)->cmd->next = create_cmd(node->cmd);
			node->cmd = node->cmd->next;
		}
		tmp = tmp->next;
	}
	create_exec(&node->cmd);
}
	// free_token_list(tmp);
