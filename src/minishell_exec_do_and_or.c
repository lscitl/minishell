/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_do_and_or.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:46:22 by seseo             #+#    #+#             */
/*   Updated: 2022/06/16 23:26:25 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_and(t_b_node *root)
{
	int	status;

	status = do_left(root->left);
	if (status == 0)
		return (do_right(root->right));
	return (status);
}

int	do_or(t_b_node *root)
{
	int	status;

	status = do_left(root->left);
	if (status != 0)
		return (do_right(root->right));
	return (status);
}

int	do_parenthesis(t_b_node *root)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		if (root->right->type == BT_CMD)
			do_cmd(root->right); //?
		else if (root->right->type == BT_PIPE)
			do_pipe(root->right); //?
		else if (root->right->type == BT_PAREN)
			do_parenthesis(root->right);
	}
	else
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
}
