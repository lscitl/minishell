/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_do_cmd_child.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:10:49 by seseo             #+#    #+#             */
/*   Updated: 2022/06/27 00:45:55 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_cmd_with_actual_path(t_info *info);
static int	do_cmd_with_env_path(t_info *info, t_env_list *path_node);

int	do_cmd(t_info *info, t_b_node *root)
{
	pid_t	pid;
	int		status;

	if (is_paren(root))
		return (do_main_paren(info, root));
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

int	do_cmd_child(t_info *info, t_b_node *root)
{
	t_env_list	*path_node;
	int			redir_status;

	info->plv++;
	redir_status = apply_redir(info, root);
	if (redir_status)
		return (redir_status);
	if (info->cmd[0] == NULL)
		return (EXIT_SUCCESS);
	if (strchr(info->cmd[0], '/'))
		return (do_cmd_with_actual_path(info));
	path_node = find_key(info->env_list, "PATH");
	if (path_node)
		return (do_cmd_with_env_path(info, path_node));
	print_err_msg(info->cmd[0], "No such file or directory");
	return (ERROR_EXIT);
}

static int	do_cmd_with_actual_path(t_info *info)
{
	struct stat	statbuf;
	char		**env;

	env = get_env_strs(info);
	execve(info->cmd[0], info->cmd, env);
	if (errno == EACCES)
	{
		stat(info->cmd[0], &statbuf);
		if (S_ISDIR(statbuf.st_mode))
			print_err_msg(info->cmd[0], "is a directory");
		else
			print_err_msg(info->cmd[0], strerror(errno));
		return (ERROR_PERMISSION);
	}
	print_err_msg(info->cmd[0], strerror(errno));
	return (ERROR_EXIT);
}

static int	do_cmd_with_env_path(t_info *info, t_env_list *path_node)
{
	char	**env;
	char	**path;
	int		i;

	env = get_env_strs(info);
	path = ft_split(path_node->value, ':');
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	i = 0;
	while (path[i] && execve(ft_strjoin(path[i], info->cmd[0]), info->cmd, env)
		&& errno == ENOENT)
		i++;
	if (errno == ENOENT)
		print_err_msg(info->cmd[0], "command not found");
	else
		print_err_msg(ft_strjoin(path[i], info->cmd[0]), strerror(errno));
	return (ERROR_EXIT);
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
