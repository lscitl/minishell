/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:13:22 by seseo             #+#    #+#             */
/*   Updated: 2022/06/26 19:52:29 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*is_bool_or_pipe(t_token *token);
static t_token	*skip_paren(t_token *token);
static void		find_node_type(t_b_node *b_node, t_token *root);

void	make_parse_tree(t_b_node *b_node)
{
	t_token	*tk_root;

	if (b_node && b_node->type == BT_NONE)
	{
		tk_root = is_bool_or_pipe(b_node->tokens);
		find_node_type(b_node, tk_root);
		if (b_node->type != BT_CMD)
		{
			make_left_node(b_node->tokens, tk_root);
			b_node->left = make_btree_node(b_node->tokens);
			b_node->tokens = NULL;
			b_node->right = make_btree_node(tk_root->next);
			free(tk_root->content);
			free(tk_root);
			make_parse_tree(b_node->left);
			make_parse_tree(b_node->right);
		}
		else if (b_node->type == BT_CMD)
		{
			set_redir(b_node);
			if (is_paren(b_node))
				make_paren_node(b_node);
		}
	}
}

static t_token	*is_bool_or_pipe(t_token *token)
{
	t_token	*tmp;
	t_token	*pipe;

	tmp = token;
	pipe = NULL;
	while (tmp)
	{
		if (1 <= tmp->type && tmp->type <= 4)
			tmp = tmp->next;
		if (tmp->type == TKN_L_PT)
			tmp = skip_paren(tmp);
		if (tmp == NULL)
			return (pipe);
		if (tmp->type == TKN_AND || tmp->type == TKN_OR)
			return (tmp);
		if (tmp->type == TKN_PIPE && pipe == NULL)
			pipe = tmp;
		tmp = tmp->next;
	}
	return (pipe);
}

static t_token	*skip_paren(t_token *token)
{
	t_token	*tmp;
	int		paren_flag;

	tmp = token;
	paren_flag = 0;
	while (tmp)
	{
		if (tmp->type == TKN_L_PT)
			paren_flag++;
		else if (tmp->type == TKN_R_PT)
			paren_flag--;
		tmp = tmp->next;
		if (paren_flag == 0)
			break ;
	}
	return (tmp);
}

static void	find_node_type(t_b_node *b_node, t_token *root)
{
	if (root == NULL)
		b_node->type = BT_CMD;
	else if (root->type == TKN_AND)
		b_node->type = BT_AND;
	else if (root->type == TKN_OR)
		b_node->type = BT_OR;
	else
		b_node->type = BT_PIPE;
}
