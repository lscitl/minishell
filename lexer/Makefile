# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/13 16:10:37 by hyunkkim          #+#    #+#              #
#    Updated: 2022/06/13 22:04:08 by hyunkkim         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME=lexer
CC=cc
OPT=-L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -lreadline
SRC= main.c \
	lst.c \
	utils_libft.c \
	utils_token.c

NAME :
	$(CC) $(SRC) $(OPT) -o $(NAME)

fclean :
	rm $(NAME)

.PHONY : clean fclean
