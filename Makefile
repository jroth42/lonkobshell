# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroth <jroth@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 20:26:26 by jroth             #+#    #+#              #
#    Updated: 2022/04/05 20:05:09 by jroth            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LX = ./parse/

PRMPT = ./prompt/

EXEC = ./exec/

UTL = ./utils/

LIBFT = $(UTL)libft/

SRC =	$(PRMPT)main.c \
		$(LX)tokenize.c $(LX)token_handle.c $(LX)token_redirect.c\
		$(LX)parse_cmd.c \
		$(EXEC)exec_utils.c $(EXEC)execute.c $(EXEC)exec_redirect.c\
		$(UTL)utils.c $(UTL)print.c $(UTL)free.c

CC = gcc -g -Wall -Werror -Wextra

LIBFT = $(UTL)libft/

OBJ = $(SRC:c=o)

$(NAME): $(OBJ)
	@echo 'compiling minishell...'
	@make -C $(LIBFT)
	@$(CC) -o $(NAME) $(OBJ) $(LIBFT)libft.a -lreadline -I/Users/$(USER)/.brew/opt/readline/include -L/Users/$(USER)/.brew/opt/readline/lib 
	@make clean

%.o: %.c
	@$(CC) -c $< -o $@

clean:
	@rm -f $(PRMPT)*.o
	@rm -f $(LX)*.o
	@rm -f $(LIBFT)*.o
	@rm -f $(UTL)*.o
	@rm -f $(EXEC)*.o

fclean:
	@rm -f $(NAME)
	@rm -f $(LIBFT)libft.a

re: clean fclean $(NAME)

all: re
