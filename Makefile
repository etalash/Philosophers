# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stalash <stalash@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/25 17:07:03 by stalash           #+#    #+#              #
#    Updated: 2024/10/28 21:52:48 by stalash          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Werror -Wextra -g -pthread -I lib

SRCS = src/create.c src/destroy.c src/init.c src/main.c src/monitoring.c src/table_process.c src/utils.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(OBJ): %.o: %.c
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	cc $(CFLAGS) -o $@ $(OBJ) -pthread

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
