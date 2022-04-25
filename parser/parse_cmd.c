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

//	walk through tokens and append them to cmd struct
//	create new cmd struct if pipe is found
char	*add_cmd(t_token **token)
{
	t_string	*t_str;
	char		*ret;
	char		**env;

	env = return_env(NULL);
	t_str = s_create();
	while ((*token)->next && ((*token)->type == SQUOTE
			|| (*token)->type == DQUOTE || (*token)->type == COMMAND
			|| (*token)->type == ARG))
	{
		s_add_str(t_str, (*token)->chr);
		(*token) = (*token)->next;
		if (t_str->str[0] != '/' && !access(find_path(t_str->str, env), F_OK))
			break ;
	}
	ret = s_get_str(t_str);
	s_destroy(t_str);
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
	create_exec(&node->cmd);
}
