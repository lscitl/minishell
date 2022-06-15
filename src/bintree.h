/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bintree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 22:22:26 by seseo             #+#    #+#             */
/*   Updated: 2022/06/14 22:22:26 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINTREE_H
# define BINTREE_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/include/libft.h"

typedef struct s_b_node
{
	t_token			*tokens;
	t_redir			*redir;
	struct s_b_node	*left;
	struct s_b_node	*right;
}	t_b_node;

t_b_node	*make_btree_node(void *content);
t_b_node	*insert_left_child(t_b_node *p_node, t_b_node *node);
t_b_node	*insert_right_child(t_b_node *p_node, t_b_node *node);
t_b_node	*get_left_child(t_b_node *node);
t_b_node	*get_right_child(t_b_node *node);
void		del_btree(t_b_node *root_node);
void		del_btree_node(t_b_node *node);

void		preorder_b_tree(t_b_node *p_node);
void		inorder_b_tree(t_b_node *p_node);
void		postorder_b_tree(t_b_node *p_node);

// t_b_node	*searchBinTreeNode(t_b_node *root_node, char c);

#endif
