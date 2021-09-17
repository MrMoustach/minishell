# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 15:27:14 by iharchi           #+#    #+#              #
#    Updated: 2020/03/09 18:26:13 by iharchi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = 	ft_memset.c 		\
		ft_bzero.c			\
		ft_memcpy.c			\
		ft_memccpy.c		\
		ft_memmove.c		\
		ft_memchr.c			\
		ft_memcmp.c			\
		ft_strlen.c			\
		ft_strlcpy.c		\
		ft_strlcat.c		\
		ft_strchr.c			\
		ft_strrchr.c		\
		ft_strnstr.c		\
		ft_strncmp.c		\
		ft_atoi.c			\
		ft_isalpha.c		\
		ft_isdigit.c		\
		ft_isalnum.c		\
		ft_isascii.c		\
		ft_isprint.c		\
		ft_toupper.c		\
		ft_tolower.c		\
		ft_calloc.c			\
		ft_strdup.c			\
		ft_substr.c			\
		ft_strjoin.c		\
		ft_strtrim.c		\
		ft_split.c			\
		ft_itoa.c			\
		ft_strmapi.c		\
		ft_putchar_fd.c		\
		ft_putstr_fd.c		\
		ft_putendl_fd.c		\
		ft_putnbr_fd.c
OBJECT = $(SRC:.c=.o)
BONUS_SRC = ft_lstnew_bonus.c		\
			ft_lstadd_front_bonus.c	\
			ft_lstsize_bonus.c		\
			ft_lstlast_bonus.c		\
			ft_lstadd_back_bonus.c	\
			ft_lstdelone_bonus.c	\
			ft_lstclear_bonus.c		\
			ft_lstiter_bonus.c		\
			ft_lstmap_bonus.c
BONUS_OBJECT = $(BONUS_SRC:.c=.o)
FLAG = -Wall -Werror -Wextra
OPTIONS = -c 
all: $(NAME)
$(NAME) : 
			@gcc $(FLAG) $(OPTIONS) $(SRC)
			@ar -rsc $(NAME) $(OBJECT)
			@ranlib $(NAME)

clean:
	@/bin/rm -f $(OBJECT) $(BONUS_OBJECT)

fclean: clean
	@/bin/rm -f $(NAME)

re : fclean all

bonus : 
	@gcc $(FLAG) $(OPTIONS) $(BONUS_SRC)
	@ar -rsc $(NAME) $(BONUS_OBJECT)
	@ranlib $(NAME)

.PHONY: all clean fclean re bonus
