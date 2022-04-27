/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:33:58 by jroth             #+#    #+#             */
/*   Updated: 2022/04/27 18:41:41 by jroth            ###   ########.fr       */
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
	READ_INPUT = '<',
	HEREDOC = 240,
	TRUNCATE = '>',
	APPEND = 248,
	DOLLAR	= '$',
};

typedef struct s_token
{
	char			*chr;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_redir
{
	char			*file;
	int				type;
	struct s_redir	*next;
	struct s_redir	*prev;
}				t_redir;

typedef struct s_cmd
{
	char			**exec;
	char			*cmd;
	char			*args;
	t_redir			*redirect;
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

void	fill_arguments(t_token *token, t_cmd **cmd);
void	pipe_cmd_handle(t_node **node);
bool	check_builtin_tk(char *cmd);
void	create_exec(t_cmd **cmd);
void	parse_args(t_cmd **cmd);
bool	parser_error(t_token *token);
void	lexer(t_node *node);
t_token	*create_token(t_token *token);
void	handle_quotation(t_token **token, char **input);
void	handle_redirections(t_token **token, char **input);
void	handle_word(t_token **token, char **input);

// EXPAND
int		expander(t_token **token, char **input);
void	expand(t_token **token, char **input);
char	*env_var_variable(char **input);

// REDIRECTs
void	add_redirection(t_token *tmp, t_redir **redir);
t_redir	*get_last_in_redir(t_redir *head);

t_cmd	*create_cmd(t_cmd *cmd);
void	parse_cmd(t_node *node);
void	print_cmd(t_node *node);
bool	stringcmp(char *str, char *cmp);

#endif
