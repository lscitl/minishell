/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_do_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:33:46 by seseo             #+#    #+#             */
/*   Updated: 2022/06/26 01:02:35 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_pipe(t_b_node *root);
static void	do_pipe_child(t_info *info, t_b_node *root, t_pipe_args args);
static int	do_pipe_final_cmd(t_info *info, t_b_node *root, t_pipe_args args);

int	do_pipe(t_info *info, t_b_node *root)
{
	t_pipe_args	args;
	int			i;

	i = 0;
	args.prev_pipe = -1;
	args.n_pipe = count_pipe(root);
	// fprintf(stderr, "pipe\n");
	while (i++ < args.n_pipe)
	{
		if (pipe(args.pipe_oi))
			error_exit_wait(i - 1);
		args.pid = fork();
		if (args.pid == -1)
			error_exit_wait(i - 1);
		else if (args.pid == 0)
			do_pipe_child(info, root->left, args);
		else
		{
			close(args.pipe_oi[1]);
			if (args.prev_pipe != -1)
				close(args.prev_pipe);
			args.prev_pipe = args.pipe_oi[0];
			root = root->right;
		}
	}
	return (do_pipe_final_cmd(info, root, args));
}

static int	count_pipe(t_b_node *root)
{
	int	n;

	n = 0;
	while (root->type == BT_PIPE)
	{
		n++;
		root = root->right;
	}
	return (n);
}

static void	do_pipe_child(t_info *info, t_b_node *root, t_pipe_args args)
{
	int	status;

	if (args.prev_pipe != -1)
	{
		dup2(args.prev_pipe, STDIN_FILENO);
		close(args.prev_pipe);
	}
	close(args.pipe_oi[0]);
	dup2(args.pipe_oi[1], STDOUT_FILENO);
	close(args.pipe_oi[1]);
	if (is_paren(root))
		status = do_pipe_paren(info, root);
	else
	{
		info->cmd = make_cmd_strs(info, root->tokens);
		if (info->cmd[0] && is_builtin(info->cmd[0]))
			status = do_main_builtin(info, root);
		else
			status = do_cmd_child(info, root);
	}
	exit(status);
}

static int	do_pipe_final_cmd(t_info *info, t_b_node *root, t_pipe_args args)
{
	int	i;
	int	status;

	args.pid = fork();
	if (args.pid == -1)
		error_exit_wait(args.n_pipe);
	else if (args.pid == 0)
	{
		dup2(args.prev_pipe, STDIN_FILENO);
		close(args.prev_pipe);
		if (is_paren(root))
			status = do_pipe_paren(info, root);
		else
		{
			info->cmd = make_cmd_strs(info, root->tokens);
			if (info->cmd[0] && is_builtin(info->cmd[0]))
				status = do_main_builtin(info, root);
			else
				status = do_cmd_child(info, root);
		}
		exit(status);
	}
	close(args.prev_pipe);
	i = args.n_pipe + 1;
	while (i-- > 0)
		if (waitpid(-1, &args.status, 0) == args.pid)
			info->status = args.status;
	return (return_exit_status(info->status));
}

