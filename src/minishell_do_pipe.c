/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_do_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:33:46 by seseo             #+#    #+#             */
/*   Updated: 2022/06/18 17:58:45 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipe(t_b_node *root)
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

void	do_child(t_info *info, t_b_node *root)
{
	is_paren(root);
}

int	do_pipe_final_cmd(t_info *info, t_b_node *root, t_pipe_args args)
{
	int	i;

	args.pid[args.n_pipe] = fork();
	if (args.pid[args.n_pipe] == -1)
		exit(EXIT_FAILURE);
	else if (args.pid[args.n_pipe] == 0)
	{
		dup2(args.prev_pipe, STDIN_FILENO);
		close(args.prev_pipe);
		do_cmd();
		exit(EXIT_FAILURE);
	}
	close(args.prev_pipe);
	i = 0;
	while (i < args.n_pipe)
		waitpid(args.pid[i++], NULL, 0);
	waitpid(args.pid[i], &args.status, 0);
	free(args.pid);
	if (WEXITSTATUS(args.status))
		return (WEXITSTATUS(args.status));
	else if (args.status)
		return (128 + args.status);
	return (args.status);
}

int	do_pipe(t_info *info, t_b_node *root)
{
	t_pipe_args	args;
	int			i;

	args.n_pipe = count_pipe(root);
	args.pid = malloc(sizeof(pid_t) * (n_pipe + 1));
	if (args.pid == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	args.prev_pipe = -1;
	while (i < args.n_pipe)
	{
		if (pipe(args.pipe_oi))
			exit(EXIT_FAILURE);
		args.pid[i] = fork();
		if (args.pid[i] == -1)
			exit(EXIT_FAILURE);
		else if (args.pid[i] == 0)
		{
			do_child(info, root->left, args);
			exit (0);
		}
		else
		{
			close(args.pipe_oi[1]);
			if (args.prev_pipe != -1)
				close(args.prev_pipe);
			args.prev_pipe = args.pipe_oi[0];
			root = root->right;
		}
		i++;
	}
	return (do_final_cmd(info, root->left, args));
}
