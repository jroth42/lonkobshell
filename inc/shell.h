/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:16:01 by jroth             #+#    #+#             */
/*   Updated: 2022/03/22 18:56:10 by jroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../utils/libft/libft.h"

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

typedef struct		s_token
{
	char			*chr;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct		s_table
{
	char			**cmd;
	char			*exec;
	char			*args;
	char			*re_in;
	char			*re_out;
	struct s_table	*next;
	struct s_table	*prev;
}					t_table;

typedef struct		s_node
{
	char			*input;
	t_token			*token;
	t_table			*table;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

//	TOKENIZER :
void	lexer(t_node *node);
t_token	*create_token(t_token *token);
void	handle_quotation(t_token **token, char **input);
void	handle_redirections(t_token **token, char  **input);
void	handle_word(t_token **token, char **input);
void	handle_pipe(t_token **token, char **input);

//	UTILS
void	input_handle(t_node *node);
void	skip_whitespace(char **str);
bool	whitespace(const char c);

//	TABLEIZEME:
t_table	*create_cmd(t_table *table);
void	command_table(t_node *node);

void	print_table(t_node *node);
bool	stringcmp(char *str, char *cmp);