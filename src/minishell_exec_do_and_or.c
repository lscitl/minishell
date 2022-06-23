/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_do_and_or.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:46:22 by seseo             #+#    #+#             */
/*   Updated: 2022/06/23 20:29:53 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_builtin(t_info *info, char **cmd)
{
	int	status;

	status = 0;
	if (ft_strncmp(cmd[0], "echo", -1) == 0)
		status = b_echo(info, cmd);
	else if (ft_strncmp(cmd[0], "exit", -1) == 0)
	{
		if (cmd[1])
			b_exit(info, ft_atoi(cmd[1]));
		b_exit(info, 0);
	}
	else if (ft_strncmp(cmd[0], "pwd", -1) == 0)
		status = b_pwd();
	else if (ft_strncmp(cmd[0], "env", -1) == 0)
		status = b_env(info->env_list);
	else if (ft_strncmp(cmd[0], "unset", -1) == 0)
		status = b_unset(cmd, &info->env_list);
	else if (ft_strncmp(cmd[0], "cd", -1) == 0)
		status = b_cd(cmd, info);
	else
		status = b_export(cmd, info);
	free_strs(cmd);
	return (status);
}

int	do_main_builtin(t_info *info, t_b_node *root)
{
	int		io_fd[2];

	pipe(io_fd);
	close(io_fd[0]);
	close(io_fd[1]);
	dup2(STDIN_FILENO, io_fd[0]);
	dup2(STDOUT_FILENO, io_fd[1]);
	apply_redir(info, root);
	info->status = do_builtin(info, info->cmd);
	dup2(io_fd[0], STDIN_FILENO);
	close(io_fd[0]);
	dup2(io_fd[1], STDOUT_FILENO);
	close(io_fd[1]);
	return (info->status);
}

int	do_cmd(t_info *info, t_b_node *root)
{
	pid_t	pid;

	if (is_paren(root))
		return (do_paren(info, root));
	info->cmd = make_cmd_strs(info, root->tokens);
	if (info->cmd[0] && is_builtin(info->cmd[0]))
		return (do_main_builtin(info, root));
	else
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
			do_cmd_child(info, root);
		free_strs(info->cmd);
		waitpid(pid, &info->status, 0);
		if (WEXITSTATUS(info->status))
			return (WEXITSTATUS(info->status));
		return (128 + info->status);
	}
}

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
