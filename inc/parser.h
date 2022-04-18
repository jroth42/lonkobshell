/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:33:58 by jroth             #+#    #+#             */
/*   Updated: 2022/04/18 15:03:47 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

enum e_type
{
	COMMAND = 0,
	ARG = -1,
	SQUOTE = '\'',
	DQUOTE = '\"',
	PIPE = '|',
	LESS = '<',
	LESSLESS = 240,
	GREAT = '>',
	GREATGREAT = 248,
};

typedef struct s_token
{
	char			*chr;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

// typedef struct s_redir
// {
// 	t_type			type;
// 	char			*file;
// 	struct s_redir	*next;
// 	struct s_redir	*prev;
// }	t_redir;

typedef struct s_cmd
{
	char			**exec;
	char			*cmd;
	char			*args;
	char			*re_in;
	char			*re_out;
	int				re_type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_node
{
	char			*input;
	t_token			*token;
	t_cmd			*cmd;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

void	lexer(t_node *node);
t_token	*create_token(t_token *token);
void	handle_quotation(t_token **token, char **input);
void	handle_redirections(t_token **token, char **input);
void	handle_word(t_token **token, char **input);
void	handle_pipe(t_token **token, char **input);

t_cmd	*create_cmd(t_cmd *cmd);
void	parse_cmd(t_node *node);
void	print_cmd(t_node *node);
bool	stringcmp(char *str, char *cmp);

#endif
