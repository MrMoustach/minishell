# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/02 11:16:24 by iharchi           #+#    #+#              #
#    Updated: 2021/02/02 15:49:26 by iharchi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniShell

GNL = gnl/*.c
SRC = 	srcs/*.c
LIBFT = libft/
FLAG =   -D BUFFER_SIZE=32 -Wall -Werror -Wextra
all: $(NAME)
$(NAME) : 
			@echo "\033[0;33mMaking LIBFT"
			@$(MAKE) -C $(LIBFT)
			@$(MAKE) -C $(LIBFT) bonus
			@echo "\033[0;33mCompiling MINISHELL"
			@gcc $(FLAG) main.c $(LIBFT)libft.a $(SRC) $(GNL) -o $(NAME)
			@echo "\033[0;32mReady to use.\n\033[0;33mDo ./miniShell"
clean:
	@$(MAKE) -C $(LIBFT) clean
	@echo "\033[0;32mDone."
fclean: clean
	@/bin/rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@echo "\033[0;32mEverything is cleaned"

re : fclean all

test :
			@gcc  -g main.c $(SRC)  $(GNL) $(LIBFT)libft.a $(FLAG) -o $(NAME)	
.PHONY: all clean fclean re