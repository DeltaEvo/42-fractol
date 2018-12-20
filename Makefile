# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 16:01:17 by dde-jesu          #+#    #+#              #
#    Updated: 2018/12/20 11:36:55 by dde-jesu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fractol
CFLAGS=-Wall -Werror -Wextra -Iinclude -Ilibft/include -O3
CC=gcc

include src.mk

OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(OBJS): Makefile src.mk

$(NAME): $(OBJS)
	$(MAKE) -C libft libft.a
	$(CC) -lmlx -lpthread -lm -framework OpenGL -framework AppKit -o $(NAME) $(OBJS) libft/libft.a
#	$(CC) $(CFLAGS) -L../minilibx -o $(NAME) $(OBJS) libft/libft.a -lmlx $(shell pkg-config --libs x11) $(shell pkg-config --libs xext) -lm

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
