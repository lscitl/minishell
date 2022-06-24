/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_do_and_or.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:46:22 by seseo             #+#    #+#             */
/*   Updated: 2022/06/24 15:57:43 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_and_or(t_info *info, t_b_node *root, enum e_and_or and_or)
{
	int	status;

	if (root->left->type == BT_CMD)
		status = do_cmd(info, root->left);
	else
		status = do_pipe(info, root->left);
	if (and_or == !!status)
	{
		if (root->right->type == BT_CMD)
			status = do_cmd(info, root->right);
		else if (root->right->type == BT_PIPE)
			status = do_pipe(info, root->right);
		else if (root->right->type == BT_AND)
			status = do_and_or(info, root->right, CMD_AND);
		else if (root->right->type == BT_OR)
			status = do_and_or(info, root->right, CMD_OR);
	}
	return (status);
}
