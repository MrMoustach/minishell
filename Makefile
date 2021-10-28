# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/17 14:26:01 by zed               #+#    #+#              #
#    Updated: 2021/10/28 16:13:02 by iharchi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# TODO: Explicitily declare the srcs
SRCS = $(wildcard srcs/*.c srcs/**/*.c src/**/**/*.c)

# Objs config ---
OBJS = $(subst srcs/,build/, $(patsubst %.c,%.o,$(SRCS)))
OBJ_FLAG = -c -I./headers -I$(HOME_BREW)/opt/readline/include
FLAGS =  -L $(HOME_BREW)/opt/readline/lib -lreadline -g

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
	gcc $(OBJS) $(LIBFT) $(FLAGS) -o $(NAME) -fsanitize=address

$(LIBFT):
	make -sC ./libft
	make -sC ./libft bonus
	make -sC ./libft clean
	mkdir -p ./libs
	cp libft/libft.a libs/

test: $(OBJS) $(LIBFT)
	gcc $(OBJS) $(LIBFT)  $(FLAGS) -o $(NAME) 

build/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	gcc $<  $(OBJ_FLAG) -g  -o $@

.PHONY: all clan fclean re test