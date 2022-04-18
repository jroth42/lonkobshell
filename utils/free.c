/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:02:17 by jroth             #+#    #+#             */
/*   Updated: 2022/04/18 21:38:48 by jroth            ###   ########.fr       */
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

	while (cmd)
	{
		if (cmd->exec)
			free_2d(cmd->exec);
		if (cmd->cmd)
			myfree(cmd->cmd);
		if (cmd->args)
			myfree(cmd->args);
		// if (cmd->re_in)
		// 	myfree(cmd->re_in);
		// if (cmd->re_out)
		// 	myfree(cmd->re_out);
		tmp = cmd;
		cmd = cmd->next;
		if (tmp)
			myfree(tmp);
	}
}
