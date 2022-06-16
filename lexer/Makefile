# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/13 16:10:37 by hyunkkim          #+#    #+#              #
#    Updated: 2022/06/16 16:53:40 by seseo            ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME=lexer
CC=cc
OPT=-L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -lreadline
SRC= main.c \
	lst.c \
	utils_libft.c \
	utils_token.c \
	bintree.c \
	parse.c

NAME :
	$(CC) $(SRC) $(OPT) -o $(NAME)

fclean :
	rm $(NAME)

.PHONY : clean fclean
