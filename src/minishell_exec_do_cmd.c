/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_do_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:43:35 by seseo             #+#    #+#             */
/*   Updated: 2022/06/29 14:48:58 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_cmd(t_info *info, t_b_node *root)
{
	pid_t	pid;
	int		status;

	info->cmd = make_cmd_strs(info, root->tokens);
	if (info->cmd[0] && is_builtin(info->cmd[0]))
		return (do_main_builtin(info, root));
	else
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			status = do_cmd_child(info, root);
			exit(status);
		}
		free_strs(info->cmd);
		waitpid(pid, &info->status, 0);
		return (return_exit_status(info->status));
	}
}

int	execute_bt_node(t_info *info, t_b_node *root)
{
	int	status;

	if (root->type == BT_CMD)
		status = do_cmd(info, root);
	else if (root->type == BT_PIPE)
		status = do_pipe(info, root);
	else if (root->type == BT_PAREN)
		status = do_main_paren(info, root);
	else if (root->type == BT_AND)
		status = do_and_or(info, root, CMD_AND);
	else
		status = do_and_or(info, root, CMD_OR);
	return (status);
}
