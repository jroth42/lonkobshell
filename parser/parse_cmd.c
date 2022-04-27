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
	new->cmd = NULL;
	new->exec = NULL;
	new->args = NULL;
	new->redirect = NULL;
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
	free_2d(args);
}

char	*add_cmd(t_token **token)
{
	char		*ret;

	if (check_builtin_tk((*token)->chr))
		return (ft_strdup((*token)->chr));
	if ((*token)->chr[0] == '/')
		return (ft_strdup((*token)->chr));
	ret = ft_strdup((*token)->chr);
	(*token) = (*token)->next;
	return (ret);
}

void	parse_cmd(t_node *node)
{
	t_token	*tmp;

	tmp = node->token;
	while (tmp && tmp->prev)
		tmp = tmp->prev;
	node->cmd = create_cmd(NULL);
	while (tmp->next && !parser_error(tmp))
	{
		if (tmp->type == COMMAND)
			(node)->cmd->cmd = add_cmd(&tmp);
		if (!tmp->next)
			break ;
		else if (tmp->type == ARG || tmp->type == SQUOTE
			|| tmp->type == DQUOTE || tmp->type == DOLLAR)
			fill_arguments(tmp, &node->cmd);
		else if (tmp->type == READ_INPUT || tmp->type == HEREDOC
			|| tmp->type == TRUNCATE || tmp->type == APPEND)
			add_redirection(tmp, &node->cmd->redirect);
		else if (tmp->type == PIPE)
			pipe_cmd_handle(&node);
		tmp = tmp->next;
	}
	if (node->cmd->cmd)
		create_exec(&node->cmd);
}
