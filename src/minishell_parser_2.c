/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:43:37 by seseo             #+#    #+#             */
/*   Updated: 2022/06/26 20:00:07 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_left_node(t_token	*token, t_token *root)
{
	if (!token || !root)
		return ;
	while (token->next)
	{
		if (token->next == root)
			break ;
		token = token->next;
	}
	token->next = NULL;
}

void	make_paren_node(t_b_node *root)
{
	t_token	*tmp;
	t_token	*l_paren;
	t_token	*r_paren;

	root->type = BT_PAREN;
	l_paren = root->tokens;
	tmp = root->tokens;
	while (tmp->next->next != NULL)
		tmp = tmp->next;
	r_paren = tmp->next;
	tmp->next = NULL;
	root->right = make_btree_node(l_paren->next);
	l_paren->next = r_paren;
	make_parse_tree(root->right);
}
