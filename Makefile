# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroth <jroth@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 20:26:26 by jroth             #+#    #+#              #
#    Updated: 2022/03/19 21:07:52 by jroth            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LX = ./lx/

PRMPT = ./prompt/

UTL = ./utils/

LIBFT = $(UTL)libft/

SRC =	$(PRMPT)main.c \
		$(LX)tokenize.c $(LX)handle_token.c $(LX)cmdtable.c $(LX)fill_table.c\
		$(LX)handle_redirect.c \
		$(UTL)utils.c $(UTL)print.c

CC = gcc -g
#-Wall -Werror -Wextra

LIBFT = $(UTL)libft/

OBJ = $(SRC:c=o)

$(NAME): $(OBJ)
	make -C $(LIBFT) all
	$(CC) -o $(NAME) $(OBJ) $(LIBFT)libft.a -lreadline -I/Users/$(USER)/.brew/opt/readline/include -L/Users/$(USER)/.brew/opt/readline/lib 
	make clean

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f ./prompt/*.o
	rm -f ./lx/*.o
	rm -f $(LIBFT)*.o
	rm -f $(UTL)*.o

fclean:
	rm -f $(NAME)
	rm -f $(LIBFT)libft.a

re: clean fclean $(NAME)

all: re
