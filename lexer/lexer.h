/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:03:04 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/13 21:50:27 by hyunkkim         ###   ########seoul.kr  */
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

typedef	struct	s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

typedef	struct	s_token
{
	enum e_token	type;
	char			*content;
	t_list			*expansion_record;
	struct s_token	*next;
}	t_token;

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

#endif
