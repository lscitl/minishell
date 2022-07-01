/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_do_paren.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:28:03 by seseo             #+#    #+#             */
/*   Updated: 2022/07/02 00:28:31 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	backup_paren_std_fd(int *io_fd);
static void	restore_paren_std_fd(int *io_fd);

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

	redir_status = apply_redir(info, root);
	if (redir_status)
		return (redir_status);
	info->in_pt++;
	info->status = execute_bt_node(info, root->right);
	return (info->status);
}

int	do_main_paren_cmd_only(t_info *info, t_b_node *root)
{
	int	io_fd[2];
	int	redir_status;

	redir_status = 0;
	if (root->redir)
	{
		backup_paren_std_fd(io_fd);
		redir_status = apply_redir(info, root);
	}
	if (redir_status)
	{
		restore_paren_std_fd(io_fd);
		return (redir_status);
	}
	info->in_pt++;
	info->status = execute_bt_node(info, root->right);
	if (root->redir)
		restore_paren_std_fd(io_fd);
	return (info->status);
}

static void	backup_paren_std_fd(int *io_fd)
{
	io_fd[0] = dup(STDIN_FILENO);
	io_fd[1] = dup(STDOUT_FILENO);
	if (io_fd[0] == -1 || io_fd[1] == -1)
		exit(EXIT_FAILURE);
}

static void	restore_paren_std_fd(int *io_fd)
{
	int		rd_fd[2];

	rd_fd[0] = dup(STDIN_FILENO);
	rd_fd[1] = dup(STDOUT_FILENO);
	close(rd_fd[0]);
	close(rd_fd[1]);
	dup2(io_fd[0], STDIN_FILENO);
	close(io_fd[0]);
	dup2(io_fd[1], STDOUT_FILENO);
	close(io_fd[1]);
}
