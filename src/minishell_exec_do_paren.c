/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_do_paren.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:28:03 by seseo             #+#    #+#             */
/*   Updated: 2022/06/29 22:36:02 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_main_paren(t_info *info, t_b_node *root)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		info->plv++;
		info->status = do_pipe_paren(info, root);
		exit(info->status);
	}
	waitpid(pid, &info->status, 0);
	return (return_exit_status(info->status));
}

int	do_pipe_paren(t_info *info, t_b_node *root)
{
	int	redir_status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	redir_status = apply_redir(info, root);
	if (redir_status)
		return (redir_status);
	info->in_pt++;
	info->status = execute_bt_node(info, root->right);
	return (info->status);
}
