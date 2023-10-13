# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorais- <gmorais-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/09 11:25:38 by gmorais-          #+#    #+#              #
#    Updated: 2023/10/03 12:03:51 by gmorais-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC		=	cc
CFLAGS	=	-g -Wall -Werror -Wextra -pthread

SRC		=	main.c utils.c\
			magia.c actions.c\

all:		$(NAME)

$(NAME):
			@$(CC) $(CFLAGS) -o $(NAME) $(SRC)

clean:
			@rm -f $(NAME) 
fclean:		clean

re:			fclean all