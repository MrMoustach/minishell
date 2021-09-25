# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/17 14:26:01 by zed               #+#    #+#              #
#    Updated: 2021/09/25 09:51:39 by iharchi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME = minishell

# SRC = 	srcs/*.c
# LIBFT = libft/
# FLAG = -I./headers -lreadline  #-Wall -Werror -Wextra
# all: $(NAME)
# $(NAME) : 
# 			@echo "\033[0;33mMaking LIBFT"
# 			@$(MAKE) -C $(LIBFT)
# 			@$(MAKE) -C $(LIBFT) bonus
# 			@$(MAKE) -C $(LIBFT) clean
# 			@echo "\033[0;33mCompiling MINISHELL"
# 			@gcc  main.c $(FLAG) $(LIBFT)libft.a $(SRC) -o $(NAME)
# 			@echo "\033[0;32mReady to use.\n\033[0;33mDo ./miniShell"
# clean:
# 	@$(MAKE) -C $(LIBFT) clean
# 	@echo "\033[0;32mDone."
# fclean: clean
# 	@/bin/rm -f $(NAME)
# 	@$(MAKE) -C $(LIBFT) fclean
# 	@echo "\033[0;32mEverything is cleaned"

# re : fclean all

# test :
# 			@gcc  -g  $(FLAG) $(SRC) $(LIBFT)libft.a main.c -o $(NAME) 	
# .PHONY: all clean fclean re test

NAME = minishell

SRCS = $(wildcard srcs/*.c srcs/**/*.c)
OBJS = $(subst srcs/,build/, $(patsubst %.c,%.o,$(SRCS)))

OBJ_FLAG = -c -I./headers -I$(HOME_BREW)/opt/readline/include

FLAGS =  -L $(HOME_BREW)/opt/readline/lib -lreadline

LIBFT = libs/libft.a

all: $(NAME)

clean:
	rm -rf $(OBJS)
	make -sC ./libft clean
	rm -rf $(LIBFT)

fclean: clean
	rm -rf $(NAME)
	make -sC ./libft fclean
	rm -rf build/

re: fclean all

$(NAME): $(OBJS) $(LIBFT)
	gcc $(OBJS) $(LIBFT) $(FLAGS) -o $(NAME)

$(LIBFT):
	make -sC ./libft
	make -sC ./libft bonus
	make -sC ./libft clean
	mkdir -p ./libs
	cp libft/libft.a libs/

test: $(OBJS) $(LIBFT)
	gcc $(OBJS) $(LIBFT)  -g $(FLAGS) -o $(NAME)

build/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	gcc $<  $(OBJ_FLAG)  -o $@

.PHONY: all clan fclean re test