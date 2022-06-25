/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bintree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:07:31 by seseo             #+#    #+#             */
/*   Updated: 2022/06/25 20:04:45 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_content(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		fprintf(stderr, "%s ", tmp->content);
		tmp = tmp->next;
	}
	fprintf(stderr, "\n");
}

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

t_b_node	*insert_left_child(t_b_node *p_node, t_b_node *node)
{
	if (p_node->left != NULL)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	p_node->left = node;
	return (p_node);
}

t_b_node	*insert_right_child(t_b_node *p_node, t_b_node *node)
{
	if (p_node->right != NULL)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	p_node->right = node;
	return (p_node);
}

t_b_node	*get_left_child(t_b_node *node)
{
	if (node == NULL)
		return (NULL);
	return (node->left);
}

t_b_node	*get_right_child(t_b_node *node)
{
	if (node == NULL)
		return (NULL);
	return (node->right);
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

void	preorder_btree(t_b_node *p_node)
{
	if (p_node == NULL)
		return ;
	if (p_node->type == BT_CMD)
	{
		print_content(p_node->tokens);
		print_content(p_node->redir);
	}
}

void	inorder_btree(t_b_node *p_node)
{
	if (p_node == NULL)
		return ;
	inorder_btree(p_node->left);
	fprintf(stderr, "CMD_TYPE: %d\n", p_node->type);
	fprintf(stderr, "token: ");
	print_content(p_node->tokens);
	fprintf(stderr, "redir: ");
	print_content(p_node->redir);
	fprintf(stderr, "\n");
	inorder_btree(p_node->right);
}

void	postorder_btree(t_b_node *p_node)
{
	if (p_node == NULL)
		return ;
	postorder_btree(p_node->left);
	postorder_btree(p_node->right);
	// do something
	// printf("%c ", p_node->data);
}

// static t_b_node	*preorderSearch(t_b_node *p_node, char c)
// {
// 	t_b_node	*pReturnNode = NULL;

// 	if (p_node == NULL)
// 		return (NULL);
// 	if (p_node->data == c)
// 		pReturnNode = p_node;
// 	if (pReturnNode == NULL)
// 		pReturnNode = preorderSearch(p_node->left, c);
// 	if (pReturnNode == NULL)
// 		pReturnNode = preorderSearch(p_node->right, c);
// 	return (pReturnNode);
// }

// t_b_node	*searchBinTreeNode(BinTree *pBinTree, char c)
// {
// 	return (preorderSearch(getRootNodeBT(pBinTree), c));
// }
