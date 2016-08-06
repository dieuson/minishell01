#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/06 15:31:52 by sgaudin           #+#    #+#              #
#    Updated: 2016/08/06 15:52:01 by sgaudin          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = env_test
LIBFT = ../srcs/libft/

FLAGS = -g -Wall -Wextra -Werror

FILES = main.c env.c free.c init.c other_cmds.c get_next_line.c calls.c

all: $(NAME)

$(NAME):
	@make -C $(LIBFT)
	gcc $(FLAGS) $(FILES) $(LIBFT)libft.a -o $(NAME)

clean:
	@make -C $(LIBFT) clean

fclean:
	@make -C $(LIBFT) fclean
	rm -rf $(NAME)

re: fclean all