# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/30 15:35:48 by seseo             #+#    #+#              #
#    Updated: 2022/06/29 00:18:41 by seseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LDFLAGS=-L$(HOME)/.brew/opt/readline/lib
CPPFLAGS=-I$(HOME)/.brew/opt/readline/include

SRCS_DIR 		:=	src
OBJ_DIR			:=	obj

SRC				:=	minishell_aster_1.c \
					minishell_aster_2.c \
					minishell_b_cd.c \
					minishell_b_echo.c \
					minishell_b_env.c \
					minishell_b_exit.c \
					minishell_b_export.c \
					minishell_b_pwd.c \
					minishell_b_unset.c \
					minishell_bintree.c \
					minishell_exec_do_and_or.c \
					minishell_exec_do_builtin.c \
					minishell_exec_do_cmd_child.c \
					minishell_exec_do_cmd.c \
					minishell_exec_do_paren.c \
					minishell_exec_do_pipe.c \
					minishell_here_doc.c \
					minishell_main_sub.c \
					minishell_main.c \
					minishell_parser_1.c \
					minishell_parser_2.c \
					minishell_print_err.c \
					minishell_redir.c \
					minishell_rm_quote.c \
					minishell_signal.c \
					minishell_token_error_check.c \
					minishell_tokenizer.c \
					minishell_utils_1.c \
					minishell_utils_list_1.c \
					minishell_utils_list_2.c \
					minishell_utils_parser.c \
					minishell_utils_token_1.c \
					minishell_utils_token_2.c

SRCS			:=	$(addprefix $(SRCS_DIR)/, $(SRC))
OBJS			:=	$(SRC:%.c=$(OBJ_DIR)/%.o)

NAME			:=	minishell
CC				:=	gcc
RM				:=	rm -rf
CFLAGS			:=	-Wall -Wextra -Werror -Iinclude -g #-fsanitize=address,undefined
LIB_PATH		:=	libft

$(OBJ_DIR)/%.o:		$(SRCS_DIR)/%.c
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

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

bonus:				all

.PHONY:				all clean fclean re
