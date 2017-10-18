#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esterna <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/26 17:01:46 by esterna           #+#    #+#              #
#    Updated: 2017/10/16 20:57:03 by esterna          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CFLAGS = -Wall -Wextra -Werror -framework OpenGL -framework Appkit
DEPS = libft.a\
	   libmlx.a\
	   libftprintf.a
FUNCTIONS = $(wildcard *.c)

all: $(NAME)

$(NAME): 
	@gcc $(CFLAGS) -g -o $(NAME) $(FUNCTIONS) $(DEPS)

clean:

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -rf *.dSYM

re: fclean all
