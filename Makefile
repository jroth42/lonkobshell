# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hngo <hngo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 20:26:26 by jroth             #+#    #+#              #
#    Updated: 2022/04/18 21:33:52 by hngo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LX = ./parser/

BLT = ./built_in/

PRMPT = ./prompt/

EXEC = ./exec/

UTL = ./utils/

LIBFT = $(UTL)libft/

SRC =	$(PRMPT)main.c \
		$(LX)tokenize.c $(LX)token_handle.c $(LX)token_redirect.c\
		$(LX)parse_cmd.c \
		$(EXEC)exec_utils.c $(EXEC)execute.c $(EXEC)exec_redirect.c\
		$(EXEC)check_builtin.c\
		$(UTL)utils.c $(UTL)print.c $(UTL)free.c \
		$(BLT)env.c $(BLT)export.c $(BLT)unset.c \

CC = gcc 

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
	@rm -f $(BLT)*.o

fclean:
	@rm -f $(NAME)
	@rm -f $(LIBFT)libft.a

re: clean fclean $(NAME)

all: re
