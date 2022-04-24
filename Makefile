# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroth <jroth@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 20:26:26 by jroth             #+#    #+#              #
#    Updated: 2022/04/24 21:31:32 by jroth            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LX = ./parser/

BLT = ./built_in/

PRMPT = ./prompt/

EXEC = ./exec/

UTL = ./utils/

LIBFT = $(UTL)libft/

SRC =	$(PRMPT)main.c $(PRMPT)signals.c \
		$(LX)tokenize.c $(LX)token_handle.c $(LX)token_redirect.c \
		$(LX)parse_cmd.c $(LX)redirect_list.c  $(LX)expander.c\
		$(EXEC)exec_utils.c $(EXEC)execute.c \
		$(EXEC)check_builtin.c $(EXEC)route_stdin.c $(EXEC)route_stdout.c $(EXEC)here_doc.c\
		$(UTL)utils.c $(UTL)print.c $(UTL)free.c $(UTL)stringbuilder.c \
		$(BLT)env.c $(BLT)env_utils.c $(BLT)echo.c $(BLT)exit.c $(BLT)export.c $(BLT)unset.c

CC = gcc -g -Wall -Werror -Wextra

LIBFT = $(UTL)libft/

OBJ = $(SRC:c=o)

$(NAME): $(OBJ)
	@echo 'compiling minishell...'
	@make -C $(LIBFT)
	@$(CC) -o $(NAME) $(OBJ) $(LIBFT)libft.a -L$(HOME)/.brew/opt/readline/lib -lreadline
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

fclean:
	@rm -f $(NAME)
	@rm -f $(LIBFT)libft.a

re: clean fclean $(NAME)

all: re
