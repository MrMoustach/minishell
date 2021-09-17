# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zed <zed@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/17 14:26:01 by zed               #+#    #+#              #
#    Updated: 2021/09/17 14:26:46 by zed              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = 	srcs/*.c
LIBFT = libft/
FLAG =  -Wall -Werror -Wextra
all: $(NAME)
$(NAME) : 
			@echo "\033[0;33mMaking LIBFT"
			@$(MAKE) -C $(LIBFT)
			@$(MAKE) -C $(LIBFT) bonus
			@$(MAKE) -C $(LIBFT) clean
			@echo "\033[0;33mCompiling MINISHELL"
			@gcc $(FLAG) main.c $(LIBFT)libft.a $(SRC) -o $(NAME)
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
			@gcc  -g main.c $(SRC) $(LIBFT)libft.a $(FLAG) -o $(NAME) 	
.PHONY: all clean fclean re