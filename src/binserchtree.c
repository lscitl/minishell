/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binserchtree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:07:31 by seseo             #+#    #+#             */
/*   Updated: 2022/06/08 22:45:15 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binsearchtree.h"
#include "libft/include/libft.h"

t_bst	*make_bst()
{
	t_bst	*bst;

	bst = malloc(sizeof(t_bst));
	if (bst == NULL)
		return (NULL);
	bst->root_node = NULL;
	bst->n_bst = 0;
	return (bst);
}

t_bstnode	*search_bst(t_bst *bst, char *key)
{
	t_bstnode	*return_node;
	int			diff;

	return_node = bst->root_node;
	while (return_node != NULL)
	{
		diff = ft_strncmp(return_node->key, key, -1);
		if (diff == 0)
			break ;
		else if (diff > 0)
			return_node = return_node->l_child;
		else
			return_node = return_node->r_child;
	}
	return (return_node);
}

int	insert_bst_node(t_bst *bst, t_bstnode element)
{
	t_bstnode	*node;
	t_bstnode	*pre_node;

	if (search_bst(bst, element.key))
		return (FALSE);
	node = bst->root_node;
	if (node == NULL)
	{
		if (insert_root_node(bst, element))
			return (TRUE);
		return (FALSE);
	}
	while (node != NULL)
	{
		pre_node = node;
		if (node->key == element.key)
			break ;
		else if (element.key < node->key)
			node = node->l_child;
		else
			node = node->r_child;
	}
	if (element.key < pre_node->key)
		insert_l_child_node(pre_node, element);
	else
		insert_r_child_node(pre_node, element);
	return (TRUE);
}

t_bstnode	*insert_root_node(t_bst *bst, t_bstnode element)
{
	t_bstnode	*new_node;

	if (bst == NULL)
		return (NULL);
	new_node = malloc(sizeof(t_bstnode));
	if (new_node == NULL)
		return (NULL);
	*new_node = element;
	new_node->l_child = NULL;
	new_node->r_child = NULL;
	new_node->visited = 0;
	bst->root_node = new_node;
	return (new_node);
}

// 트리 생성시 root 주소가 무조건 있어야하므로 따로 NULL 체크 안함.
t_bstnode	*insert_l_child_node(t_bstnode *parent_node, t_bstnode element)
{
	t_bstnode	*child_node;

	if (parent_node->l_child != NULL)
		return (NULL);
	child_node = malloc(sizeof(t_bstnode));
	if (child_node == NULL)
		return (NULL);
	*child_node = element;
	child_node->l_child = NULL;
	child_node->r_child = NULL;
	parent_node->l_child = child_node;
	return (child_node);
}

t_bstnode	*insert_r_child_node(t_bstnode *parent_node, t_bstnode element)
{
	t_bstnode	*child_node;

	if (parent_node->r_child != NULL)
		return (NULL);
	child_node = malloc(sizeof(t_bstnode));
	if (child_node == NULL)
		return (NULL);
	*child_node = element;
	child_node->l_child = NULL;
	child_node->r_child = NULL;
	parent_node->r_child = child_node;
	return (child_node);
}

t_bstnode	*get_root_node_bst(t_bst *bst)
{
	if (bst != NULL)
		return (bst->root_node);
	return (NULL);
}

// 후위 순회로 노드 삭제 or 자식 노드가 없을 경우에만 삭제?
void	delete_bst_rec(t_bstnode *node)
{
	if (node == NULL)
		return ;
	delete_bst_rec(node->l_child);
	delete_bst_rec(node->r_child);
	free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

// 후위 순회(Postorder Traversal)로 트리 삭제.
void	delete_bst(t_bst *bst)
{
	delete_bst_rec(get_root_node_bst(bst));
	free(bst);
}

t_bstnode	*delete_bst_node(t_bst *bst, char *key)
{
	t_bstnode	*del_node;
	t_bstnode	*parent_node;
	t_bstnode	*predecessor;
	t_bstnode	*successor;
	int			child_num;

	if (search_bst(bst, key) == NULL)
		return (NULL);
	del_node = bst->root_node;
	if (bst->root_node->key == key)
	{
		child_num = !!(del_node->l_child) + !!(del_node->r_child);
		if (child_num == 0)
			bst->root_node = NULL;
		else if (child_num == 1)
		{
			if (del_node->l_child)
				bst->root_node = del_node->l_child;
			else
				bst->root_node = del_node->r_child;
		}
		else
		{
			predecessor = del_node->l_child;
			successor = predecessor->r_child;
			if (successor == NULL)
			{
				bst->root_node = predecessor;
				predecessor->r_child = del_node->r_child;
			}
			else
			{
				while (successor->r_child != NULL)
				{
					predecessor = successor;
					successor = successor->r_child;
				}
				bst->root_node = successor;
				del_node->l_child->r_child = successor->l_child;
				successor->l_child = del_node->l_child;
				successor->r_child = del_node->r_child;
			}
		}
	}
	else
	{
		del_node = bst->root_node;
		while (key != del_node->key)
		{
			parent_node = del_node;
			if (key < del_node->key)
				del_node = del_node->l_child;
			else
				del_node = del_node->r_child;
		}
		child_num = !!(del_node->l_child) + !!(del_node->r_child);
		if (child_num == 0)
		{
			if (parent_node->l_child == del_node)
				parent_node->l_child = NULL;
			else
				parent_node->r_child = NULL;
		}
		else if (child_num == 1)
		{
			if (parent_node->l_child == del_node)
			{
				if (del_node->l_child)
					parent_node->l_child = del_node->l_child;
				else
					parent_node->l_child = del_node->r_child;
			}
			else
			{
				if (del_node->l_child)
					parent_node->r_child = del_node->l_child;
				else
					parent_node->r_child = del_node->r_child;
			}
		}
		else
		{
			predecessor = del_node->l_child;
			successor = predecessor->r_child;
			if (successor == NULL)
			{
				if (parent_node->l_child == del_node)
					parent_node->l_child = predecessor;
				else
					parent_node->r_child = predecessor;
				predecessor->r_child = del_node->r_child;
			}
			else
			{
				while (successor->r_child != NULL)
				{
					predecessor = successor;
					successor = successor->r_child;
				}
				if (parent_node->l_child == del_node)
					parent_node->l_child = successor;
				else
					parent_node->r_child = successor;
				del_node->l_child->r_child = successor->l_child;
				successor->l_child = del_node->l_child;
				successor->r_child = del_node->r_child;
			}
		}
	}
	return (del_node);
}

void	preorder_trav(t_bstnode *parent_node)
{
	if (parent_node == NULL)
		return ;
	printf("%s ", parent_node->key);
	preorder_trav(parent_node->l_child);
	preorder_trav(parent_node->r_child);
}

void	inorder_trav(t_bstnode *parent_node)
{

	if (parent_node == NULL)
		return ;
	inorder_trav(parent_node->l_child);
	printf("%s ", parent_node->key);
	inorder_trav(parent_node->r_child);
}

void	postorder_trav(t_bstnode *parent_node)
{
	if (parent_node == NULL)
		return ;
	postorder_trav(parent_node->l_child);
	postorder_trav(parent_node->r_child);
	printf("%s ", parent_node->key);
}
