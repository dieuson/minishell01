#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/05 17:45:34 by dvirgile          #+#    #+#              #
#    Updated: 2016/09/13 16:27:23 by dvirgile         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = completion_dynamique
DIR_SRCS = ./srcs/
DIR_AUTO = $(DIR_SRCS)auto_completion/
FT_PRINTF = ./srcs/ft_printf/
INCLUDES = ./includes/ft_select.h ./libft/includes/libft.h \
 			$(FT_PRINTF)includes/ft_printf.h
LIBFT = ./libft/


FLAGS = -Wall -Wextra -Werror
CC = gcc

FILES = main_test.c init_file_list.c detect_auto_completion.c get_files.c \
		match_elements.c set_path.c display_completion.c build_list.c \
		set_sentence.c free_auto_completion.c get_next_line.c

SRCS = $(DIR_SRCS)main_test.c $(DIR_SRCS)init_file_list.c \
		$(DIR_AUTO)detect_auto_completion.c $(DIR_AUTO)get_files.c \
		$(DIR_AUTO)match_elements.c $(DIR_AUTO)set_path.c \
		$(DIR_AUTO)display_completion.c $(DIR_AUTO)build_list.c \
		$(DIR_AUTO)set_sentence.c $(DIR_AUTO)free_auto_completion.c \
		$(DIR_SRCS)get_next_line/get_next_line.c
BIN = $(FILES:.c=.o)
TILDE = $(SRC:.c=.c~) Makefile~

all: $(NAME)

$(NAME):
	@make -C $(FT_PRINTF)
	@make -C $(LIBFT)
	@printf "\033[31mCompilation $(NAME):\033[0m"
	@$(CC) $(FLAGS) $(INCLUDES) -ltermcap -Incurses  $(SRCS) -c 			
	@$(CC) $(FLAGS) $(BIN) $(FT_PRINTF)libftprintf.a $(LIBFT)libft.a \
	 -ltermcap -Incurses  -o $(NAME)
#	@$(CC) $(FLAGS) $(INCLUDES) $(SRCS) -c
#	@$(CC) $(FLAGS) -ltermcap -lncurses $(BIN) $(FT_PRINTF)libftprintf.a $(LIBFT)libft.a \
#	 -o $(NAME)
	@mkdir bin_folder
	@mv $(BIN) ./bin_folder
	@printf "\033[32m done!\n\033[0m"

clean:
	@printf "\033[31mCleaning:\033[0m"
	@rm -rf $(TILDE) ./bin_folder
	@printf "\033[32m $(NAME) bin_folder\033[0m"
#	@make -C $(LIBFT) clean
#	@make -C $(FT_PRINTF) clean
	@printf "\033[32m 	  libft bin\033[0m"
	@printf "\033[32m [done]\n\033[0m"

fclean: clean
	@printf "\033[31mCleaning:\033[0m"
	@rm -rf $(NAME)
	@printf "\033[32m $(NAME) executable\033[0m\n"
#	@make -C $(LIBFT) fclean
#	@make -C $(FT_PRINTF) fclean
re: fclean all
