# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/17 14:26:01 by zed               #+#    #+#              #
#    Updated: 2021/11/03 21:05:48 by iharchi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	srcs/env.c\
		srcs/env_helper.c\
		srcs/init.c\
		srcs/main.c\
		srcs/signals.c\
		srcs/tokens.c\
		srcs/utils.c\
		srcs/utils2.c\
		srcs/builtins/cd.c\
		srcs/builtins/echo.c\
		srcs/builtins/env.c\
		srcs/builtins/execute.c\
		srcs/builtins/exit.c\
		srcs/builtins/export.c\
		srcs/builtins/pwd.c\
		srcs/builtins/unset.c\
		srcs/errors/errors.c\
		srcs/execution/exec_proto.c\
		srcs/execution/exec_proto_bin.c\
		srcs/execution/exec_proto_utils.c\
		srcs/execution/pipe_and_redirect.c\
		srcs/execution/pipe_and_redirect_helper.c\
		srcs/execution/redirect_append.c\
		srcs/expansion/exp_route.c\
		srcs/expansion/exp_str.c\
		srcs/expansion/exp_str_size.c\
		srcs/expansion/exp_stripe.c\
		srcs/expansion/exp_utils.c\
		srcs/expansion/expansion.c\
		srcs/parser/parser.c\
		srcs/parser/parser_utils.c\
		srcs/parser/reparser.c\
		srcs/parser/spliter.c\
		srcs/parser/spliter_utils.c\
		srcs/parser/syntax.c\
		srcs/parser/tokenizer.c

# Objs config ---
OBJS = 	build/env.o\
		build/env_helper.o\
		build/init.o\
		build/main.o\
		build/signals.o\
		build/tokens.o\
		build/utils.o\
		build/utils2.o\
		build/builtins/cd.o\
		build/builtins/echo.o\
		build/builtins/env.o\
		build/builtins/execute.o\
		build/builtins/exit.o\
		build/builtins/export.o\
		build/builtins/pwd.o\
		build/builtins/unset.o\
		build/errors/errors.o\
		build/execution/exec_proto.o\
		build/execution/exec_proto_bin.o\
		build/execution/exec_proto_utils.o\
		build/execution/pipe_and_redirect.o\
		build/execution/pipe_and_redirect_helper.o\
		build/execution/redirect_append.o\
		build/expansion/exp_route.o\
		build/expansion/exp_str.o\
		build/expansion/exp_str_size.o\
		build/expansion/exp_stripe.o\
		build/expansion/exp_utils.o\
		build/expansion/expansion.o\
		build/parser/parser.o\
		build/parser/parser_utils.o\
		build/parser/reparser.o\
		build/parser/spliter.o\
		build/parser/spliter_utils.o\
		build/parser/syntax.o\
		build/parser/tokenizer.o
OBJ_FLAG = -c -I./headers -I$(HOME_BREW)/opt/readline/include -Wall -Wextra -Werror #-fsanitize=address
FLAGS =  -L $(HOME_BREW)/opt/readline/lib -lreadline -Wall -Wextra -Werror #-fsanitize=address

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

build/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	gcc $<  $(OBJ_FLAG) -g  -o $@

.PHONY: all clan fclean re test