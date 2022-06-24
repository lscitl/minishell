/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_do_paren.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:28:03 by seseo             #+#    #+#             */
/*   Updated: 2022/06/24 13:34:40 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_pipe_paren(t_info *info, t_b_node *root)
{
	if (root->right->type == BT_AND)
		return (do_and_or(info, root->right, CMD_AND));
	else if (root->right->type == BT_OR)
		return (do_and_or(info, root->right, CMD_OR));
	else if (root->right->type == BT_CMD)
		return (do_cmd(info, root->right));
	else
		return (do_pipe(info, root->right));
}

int	do_main_paren(t_info *info, t_b_node *root)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		info->plv++;
		apply_redir(info, root);
		if (root->right->type == BT_AND)
			exit(do_and_or(info, root->right, CMD_AND));
		else if (root->right->type == BT_OR)
			exit(do_and_or(info, root->right, CMD_OR));
		else if (root->right->type == BT_CMD)
			exit(do_cmd(info, root->right));
		else if (root->right->type == BT_PIPE)
			exit(do_pipe(info, root->right));
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
