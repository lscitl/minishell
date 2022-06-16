/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:03:04 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/16 21:57:24 by seseo            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

enum	e_token
{
	TKN_STR,
	TKN_INP_RD,
	TKN_OUT_RD,
	TKN_HDC_RD,
	TKN_APP_RD,
	TKN_PIPE,
	TKN_AND,
	TKN_OR,
	TKN_L_PT,
	TKN_R_PT,
	TKN_EXPAN_STR,
	TKN_QUOTE_STR,
	TKN_INVAL
};

enum	e_type
{
	BT_CMD,
	BT_AND,
	BT_OR,
	BT_PAREN,
	BT_PIPE,
	BT_NONE
};

typedef struct	s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

typedef t_list	t_redir;

typedef	struct	s_token
{
	enum e_token	type;
	char			*content;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_b_node
{
	enum e_type		type;
	t_token			*tokens;
	t_redir			*redir;
	struct s_b_node	*left;
	struct s_b_node	*right;
}	t_b_node;

// t_list func;
t_list	*ft_lstnew(void *cmd);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);

// t_token func;
t_token	*token_new(void *content);
t_token	*token_last(t_token *tokens);
void	token_add_back(t_token **tokens, t_token *new);

// utils from libft
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// bintree.c
t_b_node	*make_btree_node(void *content);
t_b_node	*insert_left_child(t_b_node *p_node, t_b_node *node);
t_b_node	*insert_right_child(t_b_node *p_node, t_b_node *node);
t_b_node	*get_left_child(t_b_node *node);
t_b_node	*get_right_child(t_b_node *node);
void		del_btree(t_b_node *root_node);
void		del_btree_node(t_b_node *node);
void		preorder_btree(t_b_node *p_node);
void		print_content(t_token *tokens);

// parse.c
void	make_parse_tree(t_b_node *b_node);

#endif
