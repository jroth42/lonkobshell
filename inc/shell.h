/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroth <jroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:16:01 by jroth             #+#    #+#             */
/*   Updated: 2022/03/18 22:40:52 by jroth            ###   ########.fr       */
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
    OPTION = -2,
    ARG,
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

typedef struct		s_node
{
	char			*input;
	t_token			*token;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct		s_table
{
	int				num;
	char			*exec;
	char			**args;
	char			*re_in;
	char			*re_out;
	struct s_table	*next;
	struct s_table	*prev;
}					t_table;


//TOKENIZER :
void	lexer(t_node *node);
t_token	*create_token(t_token *token);
void	skip_whitespace(char **str);
bool	whitespace(const char c);
void	handle_option(t_token **token, char **input);
void	handle_redirections(t_token **token, char **input);
void	handle_quotation(t_token **token, char **input);
void	handle_word(t_token **token, char **input);
	//print utils for tokenizer
void	print_tokens(t_node	*node);
void	print_nodes(t_node	*node);
bool	stringcmp(char *str, char *cmp);
void	input_handle(t_node *node);




// void	fill_table(t_table *table, t_token *token);
// t_table	*init_table();
// t_table *create_table(t_token *token);
// t_token	*token_head(t_token *token);