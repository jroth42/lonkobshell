/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:02:17 by jroth             #+#    #+#             */
/*   Updated: 2022/04/26 23:49:17 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

void	free_token_list(t_token *token)
{
	t_token	*tmp;

	while (token->prev)
		token = token->prev;
	while (token)
	{
		if (token->chr)
			myfree(token->chr);
		tmp = token;
		if (tmp)
			myfree(tmp);
		token = token->next;
	}
}

void	free_2d(char **exec)
{
	int	i;

	i = 0;
	if (exec)
	{
		if (exec[i])
		{
			while (exec[i])
				myfree(exec[i++]);
		}
		myfree(exec);
	}
}

void	free_redir_list(t_redir *red)
{
	t_redir	*tmp;

	if (red)
	{
		while (red)
		{
			tmp = red;
			if (red->file)
				myfree(red->file);
			myfree(red);
			red = tmp->next;
		}
	}
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		if (cmd->cmd)
			myfree(cmd->cmd);
		if (cmd->exec)
			free_2d(cmd->exec);
		if (cmd->args)
			myfree(cmd->args);
		if (cmd->redirect)
			free_redir_list(cmd->redirect);
		tmp = cmd;
		cmd = cmd->next;
		if (tmp)
			myfree(tmp);
	}
}

void	free_node(t_node *node)
{
	if (node)
	{
		if (node->input)
			free(node->input);
		if (node->token)
			free_token_list(node->token);
		if (node->cmd)
			free_cmd_list(node->cmd);
		myfree(node);
	}
}
