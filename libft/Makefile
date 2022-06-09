# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/11 13:53:10 by seseo             #+#    #+#              #
#    Updated: 2022/06/04 16:27:44 by seseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR			:=	src
OBJ_DIR			:=	obj

SRC				:=	$(SRC_DIR)/ft_isalpha.c \
					$(SRC_DIR)/ft_isdigit.c \
					$(SRC_DIR)/ft_isalnum.c \
					$(SRC_DIR)/ft_isascii.c \
					$(SRC_DIR)/ft_isprint.c \
					$(SRC_DIR)/ft_strlen.c \
					$(SRC_DIR)/ft_memset.c \
					$(SRC_DIR)/ft_bzero.c \
					$(SRC_DIR)/ft_memcpy.c \
					$(SRC_DIR)/ft_memmove.c \
					$(SRC_DIR)/ft_strlcpy.c \
					$(SRC_DIR)/ft_strlcat.c \
					$(SRC_DIR)/ft_toupper.c \
					$(SRC_DIR)/ft_tolower.c \
					$(SRC_DIR)/ft_strchr.c \
					$(SRC_DIR)/ft_strrchr.c \
					$(SRC_DIR)/ft_strncmp.c \
					$(SRC_DIR)/ft_memchr.c \
					$(SRC_DIR)/ft_memcmp.c \
					$(SRC_DIR)/ft_strnstr.c \
					$(SRC_DIR)/ft_atoi.c \
					$(SRC_DIR)/ft_calloc.c \
					$(SRC_DIR)/ft_strdup.c \
					$(SRC_DIR)/ft_substr.c \
					$(SRC_DIR)/ft_strjoin.c \
					$(SRC_DIR)/ft_strtrim.c \
					$(SRC_DIR)/ft_split.c \
					$(SRC_DIR)/ft_itoa.c \
					$(SRC_DIR)/ft_strmapi.c \
					$(SRC_DIR)/ft_striteri.c \
					$(SRC_DIR)/ft_putchar_fd.c \
					$(SRC_DIR)/ft_putstr_fd.c \
					$(SRC_DIR)/ft_putendl_fd.c \
					$(SRC_DIR)/ft_putnbr_fd.c

SRCB			:=	$(SRC_DIR)/ft_lstnew.c \
					$(SRC_DIR)/ft_lstadd_front.c \
					$(SRC_DIR)/ft_lstsize.c \
					$(SRC_DIR)/ft_lstlast.c \
					$(SRC_DIR)/ft_lstadd_back.c \
					$(SRC_DIR)/ft_lstdelone.c \
					$(SRC_DIR)/ft_lstclear.c \
					$(SRC_DIR)/ft_lstiter.c \
					$(SRC_DIR)/ft_lstmap.c \
					$(SRC_DIR)/ft_atol_bonus.c \
					$(SRC_DIR)/ft_strndup_bonus.c \
					$(SRC_DIR)/split_quote_bonus.c \
					$(SRC_DIR)/str_buffer_bonus.c \
					$(SRC_DIR)/ft_hextoi_bonus.c \
					$(SRC_DIR)/get_next_line_bonus.c

ifeq ($(BONUS), true)
	SRC			+=	$(SRCB)
endif

OBJ				:=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJB			:=	$(SRCB:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME			:=	libft.a
LIBC			:=	ar rcs
CC				:=	gcc
RM				:=	rm -rf
CFLAGS			:=	-Wall -Wextra -Werror -Iinclude -g

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):			$(OBJ)
					@$(LIBC) $(NAME) $(OBJ)

all:				$(NAME)

clean:
					@$(RM) $(OBJ) $(OBJB)

fclean:				clean
					$(RM) $(NAME)

re:					fclean all

bonus:
					@$(MAKE) BONUS=true

.PHONY:				all clean fclean re bonus
