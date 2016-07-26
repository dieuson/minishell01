#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/30 11:06:24 by dvirgile          #+#    #+#              #
#    Updated: 2016/07/26 12:10:59 by dvirgile         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = minishell
DIR_SRCS = ./srcs/
INCLUDES = ./includes/minishell.h ./srcs/libft/includes/libft.h ./srcs/get_next_line/get_next_line.h
LIBFT = ./srcs/libft/

FLAGS = -g -Wall -Wextra -Werror
CC = gcc

FILES = main.c get_next_line.c cd.c other_cmds.c init.c free.c
SRCS = $(DIR_SRCS)main.c srcs/get_next_line/get_next_line.c $(DIR_SRCS)cd.c\
$(DIR_SRCS)other_cmds.c $(DIR_SRCS)init.c $(DIR_SRCS)free.c
BIN = $(FILES:.c=.o)
TILDE = $(SRC:.c=.c~) Makefile~

all: $(NAME)

$(NAME):
	@make -C $(LIBFT)
	@printf "\033[31mCompilation $(NAME):\033[0m"
	@$(CC) $(FLAGS) $(SRCS) $(INCLUDES)  -c
	@$(CC) $(FLAGS) $(BIN) $(LIBFT)libft.a -o $(NAME)
	@mkdir bin_folder
	@mv $(BIN) ./bin_folder
	@printf "\033[32m done!\n\033[0m"

clean:
	@printf "\033[31mCleaning:\033[0m"
	@rm -rf $(TILDE) ./bin_folder
	@printf "\033[32m $(NAME) bin_folder\033[0m"
	@make -C $(LIBFT) clean
	@printf "\033[32m 	  libft bin\033[0m"
	@printf "\033[32m [done]\n\033[0m"

fclean: clean
	@printf "\033[31mCleaning:\033[0m"
	@rm -rf $(NAME)
	@printf "\033[32m $(NAME) executable\033[0m\n"
	@make -C $(LIBFT) fclean
##	@printf "\033[32m libft.a\n\033[0m"

re: fclean all
