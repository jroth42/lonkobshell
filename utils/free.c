/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:02:17 by jroth             #+#    #+#             */
/*   Updated: 2022/04/19 16:12:10 by jroth            ###   ########.fr       */
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
		token = token->next;
		if (tmp)
			myfree(tmp);
	}
}

void	free_2d(char **exec)
{
	int	i;

	i = 0;
	while (exec[i])
		myfree(exec[i++]);
	myfree(exec);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	// t_redir	*redir_tmp;

	while (cmd)
	{
		// if (cmd->redirect)
		// {
		// 	while (cmd->redirect)
		// 	{
		// 		redir_tmp = cmd->redirect;
		// 		cmd->redirect = cmd->redirect->next;
		// 		if (redir_tmp->file)
		// 			myfree(redir_tmp->file);
		// 		if (redir_tmp)
		// 			myfree(redir_tmp);
		// 	}
		// }
		if (cmd->exec)
			free_2d(cmd->exec);
		if (cmd->cmd)
			myfree(cmd->cmd);
		if (cmd->args)
			myfree(cmd->args);
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
		if (node->token)
			free_token_list(node->token);
		if (node->cmd)
			free_cmd_list(node->cmd);
	}
}