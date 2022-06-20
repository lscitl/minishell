# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/30 15:35:48 by seseo             #+#    #+#              #
#    Updated: 2022/06/20 21:44:30 by seseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LDFLAGS=-L/goinfre/seseo/homebrew/opt/readline/lib
CPPFLAGS=-I/goinfre/seseo/homebrew/opt/readline/include
# CC := /Users/seseo/goinfre/clang+llvm-14.0.5-x86_64-apple-darwin/bin/clang-14
SRC_DIR 		:=	src
OBJ_DIR			:=	obj

SRC				:=	$(SRC_DIR)/minishell_aster.c \
					$(SRC_DIR)/minishell_b_cd.c \
					$(SRC_DIR)/minishell_b_echo.c \
					$(SRC_DIR)/minishell_b_env.c \
					$(SRC_DIR)/minishell_b_exit.c \
					$(SRC_DIR)/minishell_b_export.c \
					$(SRC_DIR)/minishell_b_pwd.c \
					$(SRC_DIR)/minishell_b_unset.c \
					$(SRC_DIR)/minishell_bintree.c \
					$(SRC_DIR)/minishell_do_pipe.c \
					$(SRC_DIR)/minishell_exec_do_and_or.c \
					$(SRC_DIR)/minishell_here_doc.c \
					$(SRC_DIR)/minishell_list_utils_1.c \
					$(SRC_DIR)/minishell_list_utils_2.c \
					$(SRC_DIR)/minishell_main.c \
					$(SRC_DIR)/minishell_parser.c \
					$(SRC_DIR)/minishell_redir.c \
					$(SRC_DIR)/minishell_rm_quote.c \
					$(SRC_DIR)/minishell_signal.c \
					$(SRC_DIR)/minishell_token_utils.c \
					$(SRC_DIR)/minishell_tokenizer.c \
					$(SRC_DIR)/minishell_utils_1.c

OBJ				:=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME			:=	minishell
CC				:=	gcc
RM				:=	rm -rf
CFLAGS			:=	-Wall -Wextra -Werror -Iinclude -g #-fsanitize=address,undefined
LIB_PATH		:=	libft

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					@mkdir -p $(@D)
					$(CC) $(CFLAGS) -c $< -o $@ $(CPPFLAGS)

$(NAME):			$(OBJ)
					@$(MAKE) BONUS=true -C $(LIB_PATH)
					$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -Llibft -lft -lreadline -o $(NAME)

all:				$(NAME)

clean:
					$(RM) $(OBJ)
					@$(MAKE) -C $(LIB_PATH) clean

fclean:				clean
					@$(MAKE) -C $(LIB_PATH) fclean
					$(RM) $(NAME)

re:					fclean
					@$(MAKE) all

.PHONY:				all clean fclean re
