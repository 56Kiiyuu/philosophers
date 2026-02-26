# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kevlim <kevlim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/19 14:35:06 by kevlim            #+#    #+#              #
#    Updated: 2026/02/21 12:18:33 by kevlim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -g -pthread

SRCS =	init.c \
		parsing.c \
		utils.c \
		time.c \
		actions.c \
		routine.c \
		print.c \
		monitor.c \
		main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
