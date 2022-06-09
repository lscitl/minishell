/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binsearchtree.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:29:53 by seseo             #+#    #+#             */
/*   Updated: 2022/06/08 21:29:53 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINSEARCHTREE_H
# define BINSEARCHTREE_H

# include <stdio.h>
# include <stdlib.h>

typedef struct s_bstnode
{
	int					visited;
	char				*key;
	char				*value;
	struct s_bstnode	*l_child;
	struct s_bstnode	*r_child;
}	t_bstnode;

typedef struct s_bst
{
	struct s_bstnode	*root_node;
	int					n_bst;
}	t_bst;

t_bst		*make_bst(void);
t_bstnode	*get_root_node_bst(t_bst *bst);
t_bstnode	*search_bst(t_bst *bst, int key);
int			insert_bst_node(t_bst *bst, t_bstnode element);
t_bstnode	*insert_root_node(t_bst *bst, t_bstnode element);
t_bstnode	*insert_l_child_node(t_bstnode *parent_node, t_bstnode element);
t_bstnode	*insert_r_child_node(t_bstnode *parent_node, t_bstnode element);

void		delete_bst(t_bst *bst);
t_bstnode	*delete_bst_node(t_bst *bst, int key);

void		preorder_trav(t_bstnode *parent_node);
void		inorder_trav(t_bstnode *parent_node);
void		postorder_trav(t_bstnode *parent_node);

t_bstnode	*search_bst_node(t_bst *bst, char c);

#endif
