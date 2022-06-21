/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_do_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:33:46 by seseo             #+#    #+#             */
/*   Updated: 2022/06/22 00:16:59 by seseo            ###   ########.fr       */
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

void	do_child_cmd(t_info *info, t_b_node *root)
{
	char	**path;
	char	**cmd;
	char	**env;
	int		i;

	cmd = tokens_to_str(root->tokens);
	if (is_builtin(cmd[0]))
		exit(do_builtin(info, cmd));
	path = ft_split(find_key(info->env_list, "PATH")->value, ':');
	fprintf(stderr, "%s\n", cmd);
	if (path)
	{
		i = 0;
		while (path[i])
		{
			path[i] = ft_strjoin(path[i], "/");
			i++;
		}
		env = get_env_strs(info);
		i = 0;
		while (path[i] && execve(ft_strjoin(path[i++], cmd[0]), cmd, env))
			;
		execve(cmd[0], cmd, env);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit(127);
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd[0], STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	exit(127);
}

void	do_child(t_info *info, t_b_node *root, t_pipe_args args)
{
	if (args.prev_pipe != -1)
	{
		dup2(args.prev_pipe, STDIN_FILENO);
		close(args.prev_pipe);
	}
	close(args.pipe_oi[0]);
	dup2(args.pipe_oi[1], STDOUT_FILENO);
	close(args.pipe_oi[1]);
	set_redir(root);
	if (is_paren(root))
		exit(do_cmd_paren(info, root));
	apply_redir(info, root);
	do_child_cmd(info, root);
}

int	do_pipe_final_cmd(t_info *info, t_b_node *root, t_pipe_args args)
{
	char	**cmd;
	char	**path;
	char	**env;
	int		i;

	args.pid[args.n_pipe] = fork();
	if (args.pid[args.n_pipe] == -1)
		exit(EXIT_FAILURE);
	else if (args.pid[args.n_pipe] == 0)
	{
		dup2(args.prev_pipe, STDIN_FILENO);
		close(args.prev_pipe);
		set_redir(root);
		if (is_paren(root))
			exit(do_cmd_paren(info, root));
		apply_redir(info, root);
		cmd = tokens_to_str(root->tokens);
		path = ft_split(find_key(info->env_list, "PATH")->value, ':');
		if (path)
		{
			i = 0;
			while (path[i])
			{
				path[i] = ft_strjoin(path[i], "/");
				i++;
			}
			env = get_env_strs(info);
			i = 0;
			while (path[i] && execve(ft_strjoin(path[i++], cmd[0]), cmd, env))
				;
			execve(cmd[0], cmd, env);
			// ft_putendl_fd(strerror(errno), 2);???
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd[0], STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
			exit(127);
		}
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		exit(127);
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
	args.pid = malloc(sizeof(pid_t) * (args.n_pipe + 1));
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
			do_child(info, root->left, args);
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
	return (do_pipe_final_cmd(info, root, args));
}
