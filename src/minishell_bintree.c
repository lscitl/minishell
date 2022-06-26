/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bintree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:07:31 by seseo             #+#    #+#             */
/*   Updated: 2022/06/27 00:28:45 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_b_node	*make_btree_node(void *content)
{
	t_b_node	*r_node;

	r_node = malloc(sizeof(t_b_node));
	if (r_node == NULL)
		exit(EXIT_FAILURE);
	r_node->type = BT_NONE;
	r_node->tokens = content;
	r_node->redir = NULL;
	r_node->left = NULL;
	r_node->right = NULL;
	return (r_node);
}

void	del_btree(t_b_node *node)
{
	if (node == NULL)
		return ;
	del_btree(node->left);
	del_btree(node->right);
	token_del(node->tokens);
	token_del(node->redir);
	free(node);
}
