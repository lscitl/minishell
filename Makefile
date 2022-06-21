# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/30 15:35:48 by seseo             #+#    #+#              #
#    Updated: 2022/06/21 19:52:07 by seseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LDFLAGS=-L/Users/seseo/.brew/opt/readline/lib
CPPFLAGS=-I/Users/seseo/.brew/opt/readline/include

SRCS_DIR 		:=	src
OBJ_DIR			:=	obj

SRC				:=	minishell_aster.c \
					minishell_b_cd.c \
					minishell_b_echo.c \
					minishell_b_env.c \
					minishell_b_exit.c \
					minishell_b_export.c \
					minishell_b_pwd.c \
					minishell_b_unset.c \
					minishell_bintree.c \
					minishell_do_pipe.c \
					minishell_exec_do_and_or.c \
					minishell_here_doc.c \
					minishell_list_utils_1.c \
					minishell_list_utils_2.c \
					minishell_main.c \
					minishell_parser_utils.c \
					minishell_parser.c \
					minishell_redir.c \
					minishell_rm_quote.c \
					minishell_signal.c \
					minishell_token_utils.c \
					minishell_tokenizer.c \
					minishell_utils_1.c

SRCS			:=	$(addprefix $(SRCS_DIR)/, $(SRC))
OBJS			:=	$(SRC:%.c=$(OBJ_DIR)/%.o)

NAME			:=	minishell
CC				:=	gcc
RM				:=	rm -rf
CFLAGS			:=	-Wall -Wextra -Werror -Iinclude -g #-fsanitize=address,undefined
LIB_PATH		:=	libft

$(OBJ_DIR)/%.o:		$(SRCS_DIR)/%.c
					@mkdir -p $(@D)
					$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(NAME):			$(OBJS)
					@$(MAKE) BONUS=true -C $(LIB_PATH)
					$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -Llibft -lft -lreadline $(OBJS) -o $(NAME)

all:				$(NAME)

clean:
					$(RM) $(OBJS)
					@$(MAKE) -C $(LIB_PATH) clean

fclean:				clean
					@$(MAKE) -C $(LIB_PATH) fclean
					$(RM) $(NAME)

re:					fclean
					@$(MAKE) all

.PHONY:				all clean fclean re
