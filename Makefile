# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroth <jroth@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 20:26:26 by jroth             #+#    #+#              #
#    Updated: 2022/04/19 15:34:52 by jroth            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LX = ./parser/

BLT = ./built_in/

PRMPT = ./prompt/

EXEC = ./exec/

UTL = ./utils/

SGNL = ./signals/

LIBFT = $(UTL)libft/

SRC =	$(PRMPT)main.c \
		$(LX)tokenize.c $(LX)token_handle.c $(LX)token_redirect.c \
		$(LX)parse_cmd.c $(LX)redirect_list.c \
		$(EXEC)exec_utils.c $(EXEC)execute.c \
		$(EXEC)check_builtin.c $(EXEC)route_stdin.c $(EXEC)route_stdout.c $(EXEC)here_doc.c\
		$(UTL)utils.c $(UTL)print.c $(UTL)free.c \
		$(SGNL)signals.c \
		$(BLT)env.c

CC = gcc -g -Wall -Werror -Wextra

LIBFT = $(UTL)libft/

OBJ = $(SRC:c=o)

$(NAME): $(OBJ)
	@echo 'compiling minishell...'
	@make -C $(LIBFT)
	@$(CC) -o $(NAME) $(OBJ) $(LIBFT)libft.a -L$(HOME)/.brew/opt/readline/lib -lreadline -lreadline
	@make clean

%.o: %.c
	@$(CC) -I/Users/$(USER)/.brew/opt/readline/include -c $< -o $@

clean:
	@rm -f $(PRMPT)*.o
	@rm -f $(LX)*.o
	@rm -f $(LIBFT)*.o
	@rm -f $(UTL)*.o
	@rm -f $(EXEC)*.o
	@rm -f $(BLT)*.o
	@rm -f $(SGNL)*.o

fclean:
	@rm -f $(NAME)
	@rm -f $(LIBFT)libft.a

re: clean fclean $(NAME)

all: re
