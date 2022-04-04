/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:16:01 by jroth             #+#    #+#             */
/*   Updated: 2022/04/04 13:38:57 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../utils/libft/libft.h"

# define INFILE 0
# define OUTFILE 1
// # define STDIN 0
// # define STDOUT 1
// # define STDERR 2

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

typedef struct s_cmd
{
	char			**exec;
	char			*cmd;
	char			*args;
	char			*re_in;
	char			*re_out;
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

//	TOKENIZER :
void	lexer(t_node *node);
t_token	*create_token(t_token *token);
void	handle_quotation(t_token **token, char **input);
void	handle_redirections(t_token **token, char **input);
void	handle_word(t_token **token, char **input);
void	handle_pipe(t_token **token, char **input);

//	cmdIZEME:
t_cmd	*create_cmd(t_cmd *cmd);
void	parse_cmd(t_node *node);
void	print_cmd(t_node *node);
bool	stringcmp(char *str, char *cmp);

//	EXEC
char	*find_path(char *cmd, char **env);
void	eXecuTe(t_cmd *cmd, char **env);
int		strlen_to_c(char *str, char c);

//	UTILS
void	input_handle(t_node *node);
void	skip_whitespace(char **str);
bool	whitespace(const char c);

#endif