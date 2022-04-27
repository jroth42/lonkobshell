/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 01:07:09 by jroth             #+#    #+#             */
/*   Updated: 2022/04/27 18:25:50 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

bool	check_builtin_tk(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strcmp_upper_lower(cmd, "pwd")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp_upper_lower(cmd, "echo")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp_upper_lower(cmd, "env")
		|| !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "unset"))
		return (true);
	return (false);
}

// create 2D array with exec cmd at [0] if args available parse_args
void	create_exec(t_cmd **cmd)
{
	t_cmd	*head;

	while ((*cmd) && (*cmd)->prev)
		(*cmd) = (*cmd)->prev;
	head = *cmd;
	if (!(*cmd)->cmd)
		return ;
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

void	pipe_cmd_handle(t_node **node)
{
		(*node)->cmd->next = create_cmd((*node)->cmd);
		(*node)->cmd = (*node)->cmd->next;
}

void	fill_arguments(t_token *token, t_cmd **cmd)
{
	char	*join;
	char	*copy;

	copy = NULL;
	join = NULL;
	if ((*cmd)->args)
	{
		copy = ft_strjoin((*cmd)->args, " ");
		myfree((*cmd)->args);
		join = ft_strjoin(copy, token->chr);
		myfree(copy);
		(*cmd)->args = ft_strdup(join);
		myfree(join);
	}
	else
		(*cmd)->args = ft_strdup(token->chr);
}
