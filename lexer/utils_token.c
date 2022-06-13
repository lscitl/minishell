/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:07:35 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/13 19:09:56 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	find_token_type(void *content)
{
	int	type_num;

	if (ft_strncmp(content, "<", -1) == 0)
		type_num = TKN_INP_RD;
	else if (ft_strncmp(content, ">", -1 )== 0)
		type_num = TKN_OUT_RD;
	else if (ft_strncmp(content, "<<", -1) == 0)
		type_num = TKN_HDC_RD;
	else if (ft_strncmp(content, ">>", -1) == 0)
		type_num = TKN_APP_RD;
	else if (ft_strncmp(content, "|", -1) == 0)
		type_num = TKN_PIPE;
	else if (ft_strncmp(content, "&&", -1) == 0)
		type_num = TKN_AND;
	else if (ft_strncmp(content, "||", -1) == 0)
		type_num = TKN_OR;
	else if (ft_strncmp(content, "(", -1) == 0)
		type_num = TKN_L_PT;
	else if (ft_strncmp(content, ")", -1 )== 0)
		type_num = TKN_R_PT;
	else
		type_num = TKN_STR;
	return (type_num);
}

t_token	*token_new(void *content)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = find_token_type(content);
	new->content = content;
	new->expansion_record = NULL;
	new->next = NULL;
	return (new);
}

t_token	*token_last(t_token *tokens)
{
	while (tokens)
	{
		if (!tokens->next)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

void	token_add_back(t_token **tokens, t_token *new)
{
	t_token	*last;

	if (!tokens || !new)
		return ;
	if (!*tokens)
	{
		*tokens	= new;
		return ;
	}
	last = token_last(*tokens);
	last->next = new;
}
